#include <math.h>

float getNext(float t){
    float r = (cos(sin(t / 123.f) * t * 1020000.f - 23.f) + 1.) / 2.f;
    float r2 = (cos(t * 10000.f) + 1.) / 2.f;
    return (r + r2) / 2.f;
}