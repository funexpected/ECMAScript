#include "rect2.h"

#include <assert.h>
#include <stdbool.h>
#include <math.h>
#include "free_list_alloc.h"


extern FreeListAllocator rect2_allocator;

static bool js_rect2_contains_internal(const JSRect2Data* rect, const JSVector2Data* vec);
static JSRect2Data js_rect2_expand_internal(const JSRect2Data* rect, const JSVector2Data* vec);
static bool js_rect2_intersects_internal(const JSRect2Data* rect1, const JSRect2Data* rect2);

JSValue JS_NewRect2(double position_x, double position_y, double size_x, double size_y) {
    JSRect2 *rect = alloc(&rect2_allocator);
    rect->header.ref_count = 1;
    rect->data.position.x = position_x;
    rect->data.position.y = position_y;
    rect->data.size.x = size_x;
    rect->data.size.y = size_y;
    return JS_MKPTR(JS_TAG_RECT2, rect);
}

void JS_FreeRect2(JSRuntime *rt, JSRect2 *p) {
    dealloc(&rect2_allocator, p);
}

JSValue js_rect2_constructor(JSContext *ctx, JSValueConst new_target, int argc, JSValueConst *argv)
{
    if (argc == 4) {
        double args[4];

        for (int i = 0; i < 4; ++i) {
            uint32_t tag = JS_VALUE_GET_TAG(argv[i]);
            if (JS_TAG_IS_FLOAT64(tag))
                args[i] = JS_VALUE_GET_FLOAT64(argv[i]);
            else if (JS_TAG_IS_INT(tag))
                args[i] = JS_VALUE_GET_INT(argv[i]);
        }

        return JS_NewRect2(args[0], args[1], args[2], args[3]);
    } else {
        return JS_NewRect2(0.0, 0.0, 0.0, 0.0);
    }
}

JSValue js_rect2_get_position(JSContext *ctx, JSValueConst this_val)
{
    JSRect2 *r = JS_VALUE_GET_PTR(this_val);
    return JS_NewVector2(r->data.position.x, r->data.position.y);
}

JSValue js_rect2_get_size(JSContext *ctx, JSValueConst this_val)
{
    JSRect2 *r = JS_VALUE_GET_PTR(this_val);
    return JS_NewVector2(r->data.size.x, r->data.size.y);
}

JSValue js_rect2_get_end(JSContext *ctx, JSValueConst this_val)
{
    JSRect2 *r = JS_VALUE_GET_PTR(this_val);
    double end_x = r->data.position.x + r->data.size.x;
    double end_y = r->data.position.y + r->data.size.y;
    return JS_NewVector2(end_x, end_y);
}

JSValue js_rect2_contains(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
    assert(argc==1);
    uint32_t tag = JS_VALUE_GET_NORM_TAG(argv[0]);
    assert(tag == JS_TAG_VECTOR2);

    const JSRect2 *r = JS_VALUE_GET_PTR(this_val);
    const JSVector2 *v = JS_VALUE_GET_PTR(argv[0]);

    return JS_NewBool(ctx, js_rect2_contains_internal(&r->data, &v->data));
}

static bool js_rect2_contains_internal(const JSRect2Data* rect, const JSVector2Data* vec) {
    return 
        rect->position.x <= vec->x && 
        rect->position.y <= vec->y &&
        rect->position.x + rect->size.x >= vec->x &&
        rect->position.y + rect->size.y >= vec->y;
}

JSValue js_rect2_expand(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
    assert(argc==1);
    uint32_t tag = JS_VALUE_GET_NORM_TAG(argv[0]);
    assert(tag == JS_TAG_VECTOR2);

    JSRect2 *r = JS_VALUE_GET_PTR(this_val);
    const JSVector2 *v = JS_VALUE_GET_PTR(argv[0]);

    JSRect2Data new_rect = js_rect2_expand_internal(&r->data, &v->data);
    return JS_NewRect2(new_rect.position.x, new_rect.position.y, new_rect.size.x, new_rect.size.y);
}

static JSRect2Data js_rect2_expand_internal(const JSRect2Data* rect, const JSVector2Data* vec) {
    JSRect2Data new_rect = {
        .position.x = fmin(rect->position.x, vec->x),
        .position.y = fmin(rect->position.y, vec->y),
    };

    JSVector2Data end = js_vector2_add(rect->position, rect->size);
    new_rect.size.x = fmax(end.x, vec->x) - new_rect.position.x;
    new_rect.size.y = fmax(end.y, vec->y) - new_rect.position.y;

    return new_rect;
}

JSValue js_rect2_intersects(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
    assert(argc==1);
    uint32_t tag = JS_VALUE_GET_NORM_TAG(argv[0]);
    assert(tag == JS_TAG_RECT2);

    const JSRect2 *r1 = JS_VALUE_GET_PTR(this_val);
    const JSRect2 *r2 = JS_VALUE_GET_PTR(argv[0]);

    return JS_NewBool(ctx, js_rect2_intersects_internal(&r1->data, &r2->data));
}

static bool js_rect2_intersects_internal(const JSRect2Data* rect1, const JSRect2Data* rect2) {
    if (rect1->position.x >= (rect2->position.x + rect2->size.x))
        return false;
    if ((rect1->position.x + rect1->size.x) <= rect2->position.x)
        return false;
    if (rect1->position.y >= (rect2->position.y + rect2->size.y))
        return false;
    if ((rect1->position.y + rect1->size.y) <= rect2->position.y)
        return false;

    return true;
}

JSValue js_rect2_move(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
    assert(argc==1);
    uint32_t tag = JS_VALUE_GET_NORM_TAG(argv[0]);
    assert(tag == JS_TAG_VECTOR2);

    JSRect2 *r = JS_VALUE_GET_PTR(this_val);
    const JSVector2 *v = JS_VALUE_GET_PTR(argv[0]);
    
    JSRect2Data new_rect = {
        .position = js_vector2_add(r->data.position, v->data),
        .size = r->data.size,
    };

    return JS_NewRect2(new_rect.position.x, new_rect.position.y, new_rect.size.x, new_rect.size.y);
}

JSValue js_rect2_resize(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
    assert(argc==1);
    uint32_t tag = JS_VALUE_GET_NORM_TAG(argv[0]);
    assert(tag == JS_TAG_VECTOR2);

    JSRect2 *r = JS_VALUE_GET_PTR(this_val);
    const JSVector2 *v = JS_VALUE_GET_PTR(argv[0]);
    
    JSRect2Data new_rect = {
        .position = r->data.position,
        .size = js_vector2_add(r->data.size, v->data)
    };

    return JS_NewRect2(new_rect.position.x, new_rect.position.y, new_rect.size.x, new_rect.size.y);
}

JSValue JS_ToRect2(JSValueConst val)
{
    uint32_t tag;
    double position_x = 0;
    double position_y = 0;
    double size_x = 0;
    double size_y = 0;
    JSRect2 *r;
    //const char *str;
    //char buf[32];

    tag = JS_VALUE_GET_NORM_TAG(val);
    switch(tag) {
    case JS_TAG_RECT2:
        r = JS_VALUE_GET_PTR(val);
        position_x = r->data.position.x;
        position_y = r->data.position.y;
        size_x = r->data.size.x;
        size_x = r->data.size.x;
        goto new_rect;
    case JS_TAG_EXCEPTION:
        return JS_EXCEPTION;
    case JS_TAG_INT: // fall through and return new rect2
    case JS_TAG_FLOAT64:
    case JS_TAG_VECTOR2: 
    case JS_TAG_STRING: 
    case JS_TAG_BOOL:
    case JS_TAG_NULL:
    case JS_TAG_UNDEFINED:
    case JS_TAG_OBJECT:
    case JS_TAG_FUNCTION_BYTECODE:
    case JS_TAG_SYMBOL:
/*#ifdef CONFIG_BIGNUM
    case JS_TAG_BIG_INT:
    case JS_TAG_BIG_FLOAT:
    case JS_TAG_BIG_DECIMAL:
#endif */
    default:
    new_rect:
        return JS_NewRect2(position_x, position_y, size_x, size_y);
    }
}