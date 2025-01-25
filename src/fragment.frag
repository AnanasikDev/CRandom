uniform float time;
uniform vec2 resolution;

float getNext1D(float t){
    float r = (cos(sin(t / 123.0) * t * 1020.0) + 1.0) / 2.0;
    float r2 = (cos(t * 1000.0) + 1.0) / 2.0;
    return (r + r2) / 2.0;
}

float getNext2D(vec2 pos){
    float scale = 100;
    return fract(sin(dot(pos, vec2(9.7139, 200.3237)) * cos(pos.x)) * 12345.54321);
}

void main()
{
    vec2 uv = gl_FragCoord.xy / resolution.xy;
    float val = getNext2D(uv);
    gl_FragColor = vec4(val, val, val, 1.0);
}