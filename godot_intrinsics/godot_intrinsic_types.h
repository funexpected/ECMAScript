#ifndef GODOT_INTRINSIC_H
#define GODOT_INTRINSIC_H

#include "quickjs/quickjs/quickjs.h"
#include "free_list_alloc.h"

typedef struct JSVector2Data {
    double x;
    double y;
} JSVector2Data;

typedef struct JSVector2 {
    JSRefCountHeader header;
    JSVector2Data data;
} JSVector2;

typedef struct JSRect2Data {
    JSVector2Data position;
    JSVector2Data size;
} JSRect2Data;

typedef struct JSRect2 {
    JSRefCountHeader header;
    JSRect2Data data;
} JSRect2;

JSValue JS_NewVector2(double x, double y);
JSValue JS_NewRect2(double position_x, double position_y, double end_x, double end_y);
void JS_FreeVector2(JSRuntime *rt, JSVector2 *p);
void JS_FreeRect2(JSRuntime *rt, JSRect2 *p);

JSValue JS_ToVector2(JSValueConst val);
JSValue JS_ToRect2(JSValueConst val);

JSValue js_vector2_constructor(JSContext *ctx, JSValueConst new_target, int argc, JSValueConst *argv);
JSValue js_vector2_get_x(JSContext *ctx, JSValueConst this_val);
JSValue js_vector2_get_y(JSContext *ctx, JSValueConst this_val);
JSValue js_vector2_add_bind(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv);
JSValue js_rect2_constructor(JSContext *ctx, JSValueConst new_target, int argc, JSValueConst *argv);
JSValue js_rect2_get_position(JSContext *ctx, JSValueConst this_val);
JSValue js_rect2_get_size(JSContext *ctx, JSValueConst this_val);
JSValue js_rect2_get_end(JSContext *ctx, JSValueConst this_val);


#endif //GODOT_INTRINSIC_H
