uniform float time;
uniform vec2 resolution;
uniform float scale;

float getNext1D(float t){
    float r = (cos(sin(t / 123.0) * t * 1020.0) + 1.0) / 2.0;
    float r2 = (cos(t * 1000.0) + 1.0) / 2.0;
    return (r + r2) / 2.0;
}

float getNext2D(vec2 pos){
    return fract(cos(dot(pos, vec2(12.7139, 80.3237))) * 323405.84714);
}

vec2 pixelateUV(vec2 uv, float scale){
    return uv;
}

void main()
{
    vec2 uv = (gl_FragCoord.xy / resolution.xy);
    vec2 ipos = floor(uv * scale);
    float val = getNext2D(ipos); // + vec2(time / 1000.0, 0)
    gl_FragColor = vec4(val, val, val, 1.0);
}