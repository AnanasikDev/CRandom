#include <math.h>

float getNext(float t){
    float r = (cos(sin(t / 123.f) * t * 1020000.f - 23.f) + 1.) / 2.f;
    float r2 = (cos(t * 10000.f) + 1.) / 2.f;
    return (r + r2) / 2.f;
}

float getNext2D(float x, float y){
    float r = cos(x * 23.1618f + y * 7.30912f) * 438752.4711134f;
    return r - floor(r);
}