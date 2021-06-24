#include "free_list_alloc.h"
#include "vector2.h"

extern FreeListAllocator vector2_allocator;

JSValue JS_NewVector2(double x, double y) {
    JSVector2 *vec = alloc(&vector2_allocator);
    vec->header.ref_count = 1;
    vec->data.x = x;
    vec->data.y = y;
    return JS_MKPTR(JS_TAG_VECTOR2, vec);
}

void JS_FreeVector2(JSRuntime *rt, JSVector2 *p) {
    dealloc(&vector2_allocator, p);
}

JSValue js_vector2_constructor(JSContext* ctx, JSValueConst new_target, int argc, JSValueConst *argv)
{
    if (argc == 2) {
        double args[2];

        for (int i = 0; i < 2; ++i) {
            uint32_t tag = JS_VALUE_GET_TAG(argv[i]);
            if (JS_TAG_IS_FLOAT64(tag))
                args[i] = JS_VALUE_GET_FLOAT64(argv[i]);
            else if (JS_TAG_IS_INT(tag))
                args[i] = JS_VALUE_GET_INT(argv[i]);
        }

        return JS_NewVector2(args[0], args[1]);
    } else {
        return JS_NewVector2(0.0, 0.0);
    }
}

JSValue js_vector2_get_x(JSContext *ctx, JSValueConst this_val)
{
    JSVector2 *v = JS_VALUE_GET_PTR(this_val);
    return JS_NewFloat64(ctx, v->data.x);
}

JSValue js_vector2_get_y(JSContext *ctx, JSValueConst this_val)
{
    JSVector2 *v = JS_VALUE_GET_PTR(this_val);
    return JS_NewFloat64(ctx, v->data.y);
}

JSVector2Data js_vector2_add(JSVector2Data a, JSVector2Data b) {
    return (JSVector2Data) {
        .x = a.x + b.x, 
        .y = a.y + b.y
    };
}
/* unused
inline JSVector2Data js_vector2_sub(JSVector2Data a, JSVector2Data b) {
    return (JSVector2Data) {
        .x = a.x - b.x, 
        .y = a.y - b.y
    };
}

inline JSVector2Data js_vector2_mult(JSVector2Data a, JSVector2Data b) {
    return (JSVector2Data) {
        .x = a.x * b.x, 
        .y = a.y * b.y
    };
}

inline JSVector2Data js_vector2_mult_scalar(JSVector2Data a, double b) {
    return (JSVector2Data) {
        .x = a.x * b, 
        .y = a.y * b
    };
}

inline JSVector2Data js_vector2_div(JSVector2Data a, JSVector2Data b) {
    return (JSVector2Data) {
        .x = a.x / b.x, 
        .y = a.y / b.x
    };
}

inline JSVector2Data js_vector2_div_scalar(JSVector2Data a, double b) {
    return (JSVector2Data) {
        .x = a.x / b, 
        .y = a.y / b
    };
}

// inline double js_vector2_angle(JSVector2Data a) {
//     return atan(a.y, a.x);
// }
*/

JSValue js_vector2_add_bind(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    JSVector2 *v0 = JS_VALUE_GET_PTR(this_val);
    JSVector2 *v1 = JS_VALUE_GET_PTR(argv[0]);
    JSVector2Data res = js_vector2_add(v0->data, v1->data);
    return JS_NewVector2(res.x, res.y);
}

JSValue JS_ToVector2(JSValueConst val)
{
    uint32_t tag;
    JSVector2 *v;
    double x = 0;
    double y = 0;
    //const char *str;
    //char buf[32];

    tag = JS_VALUE_GET_NORM_TAG(val);
    switch(tag) {
    case JS_TAG_INT:
        x = JS_VALUE_GET_INT(val);
        y = x;
        goto new_vector;
    case JS_TAG_FLOAT64:
        x = JS_VALUE_GET_FLOAT64(val);
        y = x;
        goto new_vector;
    case JS_TAG_VECTOR2:
        v = JS_VALUE_GET_PTR(val);
        x = v->data.x;
        y = v->data.y;
        goto new_vector;
    case JS_TAG_EXCEPTION:
        return JS_EXCEPTION;
    case JS_TAG_RECT2: // fall through and return new vector2
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
    new_vector:
        return JS_NewVector2(x, y);
    }
}