uniform float u_scale;
uniform float u_time;
uniform vec2 u_resolution;
uniform vec2 u_mouse;

const bool _debug = false;

vec2 move(vec2 p){
    return vec2(p.x * abs(sin(u_time / 2.0) / 2.0), p.y);
}

vec2 random2f( vec2 p ) {
    return fract(
        sin(vec2(
            dot(p,vec2(127.1,311.7)),
            dot(p,vec2(269.5,183.3))
            ))
         * 43758.5453);
}

float random(float t){
    return random2f(vec2(t, t));
    return fract(
        dot(
            vec2(sin(t / 104.782), 8616.712), 
            cos(vec2(1293.51, t / 417.873))
            )
         * 842724.12);
}

void main(){

    vec2 uv = gl_FragCoord / u_resolution;

    vec2 st = uv * u_scale;
    vec2 i_st = floor(st);
    vec2 f_st = fract(st);

    float dist = 10.0;
    for (int x = -1; x <= 1; x++){
        for (int y = -1; y <= 1; y++){
            vec2 neighbour = vec2((float)x, (float)y);
            vec2 local_point = random2f(i_st + neighbour);
            local_point = 0.5 + 0.4*sin(u_time * 2.0 + 6.2831*local_point);
            dist = min(dist, distance(neighbour + local_point, f_st));
        }
    }

    //dist = pow(dist, 0.2) * 1.0;

    //vec3 color = mix(vec3(1.0, 0.0, 0.0), vec3(1.0, 1.0, 1.0),  dist);
    vec3 color = dist;
    //color = step(vec3(0.3), color);
    if (_debug){
        color.r += length(step(vec2(0.98), f_st));
        color += step(dist, 0.02);
    }

    gl_FragColor = vec4(color, 1.0);
}