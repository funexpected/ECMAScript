#ifndef GODOT_INTRINSIC_RECT2_H
#define GODOT_INTRINSIC_RECT2_H

#include "vector2.h"
#include "quickjs/quickjs/quickjs.h" 



typedef struct JSRect2Data {
    JSVector2Data position;
    JSVector2Data size;
} JSRect2Data;

typedef struct JSRect2 {
    JSRefCountHeader header;
    JSRect2Data data;
} JSRect2;

JSValue JS_NewRect2(double position_x, double position_y, double end_x, double end_y);
void JS_FreeRect2(JSRuntime *rt, JSRect2 *p);

JSValue JS_ToRect2(JSValueConst val);

// Methods list
JSValue js_rect2_constructor(JSContext *ctx, JSValueConst new_target, int argc, JSValueConst *argv);
JSValue js_rect2_get_position(JSContext *ctx, JSValueConst this_val);
JSValue js_rect2_get_size(JSContext *ctx, JSValueConst this_val);
JSValue js_rect2_get_end(JSContext *ctx, JSValueConst this_val);
JSValue js_rect2_contains(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv);
JSValue js_rect2_expand(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv);
JSValue js_rect2_intersects(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv);
JSValue js_rect2_move(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv);
JSValue js_rect2_resize(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv);


#endif // GODOT_INTRINSIC_RECT2_H

