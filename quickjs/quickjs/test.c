#include <stdio.h>
#include <stdlib.h>

typedef struct Header {
    int ref_count;
} Header;

typedef struct Vec2Content {
    double x;
    double y;
} Vec2Content;

typedef struct Vec2 {
    Header header;
    struct Vec2 *next;
    Vec2Content data;
} Vec2;

void print_vec(Vec2 *vec) {
    printf("Vec(%0.2f, %0.2f)\n", vec->data.x, vec->data.y);
}

Vec2Content vec2_add(const Vec2Content a, const Vec2Content b) {
    return (Vec2Content){
        .x = a.x + b.x, 
        .y =a.y + b.y
    };
    // result.x = a.x + b.x;
    // result.y = a.y + b.y;
    // return result;
}


Vec2 *vec2_new(double x, double y) {
    Vec2 *vec = (Vec2*)malloc(sizeof(Vec2));
    vec->header.ref_count = 1;
    vec->data.x = x;
    vec->data.y = y;
    return vec;
}

int main() {
    Vec2 *vec1 = vec2_new(0.0, 0.5);
    Vec2 *vec2 = vec2_new(1.2, 0.2);
    Vec2 *res = vec2_new(2.0, 3.0);
    // print_vec(res);

    printf("Size of Vec2: %d\n", sizeof(Vec2));
    // printf("Size of Header: %d\n", sizeof(Header));
    // printf("Size of Vec2Content: %d\n", sizeof(Vec2Content));
    
    // char *base;
    // base = (char *)res;
    // Vec2Content *cnt = (Vec2Content *) (base + sizeof(Header));
    // printf("Field: %0.2f \n", cnt->x);
    //BOX(res, vec2_add(UNBOX(vec1), UNBOX(vec2)));
    res->data = vec2_add(vec1->data, vec2->data);
    Vec2Content start;
    Vec2Content delta;
    for (int i=0; i<10000; i++) {
        start = vec2_add(start, delta);
    }
    print_vec(res);
}