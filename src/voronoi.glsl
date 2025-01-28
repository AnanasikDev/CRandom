
uniform float u_scale;
uniform float u_time;
uniform vec2 u_resolution;
uniform vec2 u_mouse;

vec2 move(vec2 p){
    return vec2(p.x * abs(sin(u_time / 2.0) / 2.0), p.y);
}

void main(){

    vec2 uv = gl_FragCoord / u_resolution;

    vec2 point[5];
    point[0] = move(vec2(0.83,0.75));
    point[1] = vec2(0.60,0.07);
    point[2] = vec2(0.28,0.64);
    point[3] =  vec2(0.31,0.26);
    point[4] = u_mouse / u_resolution;

    float dist = 100.0;
    for (int i = 0; i < 5; i++){
        dist = min(distance(uv, point[i]), dist);
    }

    vec3 color = vec3(dist);

    gl_FragColor = vec4(color, 1.0);
}