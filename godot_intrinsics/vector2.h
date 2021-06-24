#ifndef GODOT_INTRINSIC_VECTOR2_H
#define GODOT_INTRINSIC_VECTOR2_H

#include "quickjs/quickjs/quickjs.h" 


typedef struct JSVector2Data {
    double x;
    double y;
} JSVector2Data;

typedef struct JSVector2 {
    JSRefCountHeader header;
    JSVector2Data data;
} JSVector2;

JSValue JS_NewVector2(double x, double y);
void JS_FreeVector2(JSRuntime *rt, JSVector2 *p);

JSValue JS_ToVector2(JSValueConst val);

// Methods list
JSValue js_vector2_constructor(JSContext *ctx, JSValueConst new_target, int argc, JSValueConst *argv);
JSValue js_vector2_get_x(JSContext *ctx, JSValueConst this_val);
JSValue js_vector2_get_y(JSContext *ctx, JSValueConst this_val);
JSValue js_vector2_add_bind(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv);

// Used internally by other types
JSVector2Data js_vector2_add(JSVector2Data a, JSVector2Data b);


#endif // GODOT_INTRINSIC_VECTOR2_H