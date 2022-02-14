#version 330

#define PI 3.14159265358979323846

uniform vec2 iResolution;
uniform float iTime;
uniform vec3 roots;

in vec4 fragColor;


out vec4 outColor;

float m_sin(float t){
    return sin(t/10)*0.5 + 0.5;
}


// https://www.shadertoy.com/view/ssBGWc
vec2 cmul(vec2 a, vec2 b) {
    return vec2(a.x*b.x-a.y*b.y, a.x*b.y+a.y*b.x);
}
vec2 cdiv(vec2 a, vec2 b) { 
    return vec2(a.x*b.x+a.y*b.y, -a.x*b.y+a.y*b.x) / (b.x*b.x+b.y*b.y);
}

vec2 fn(vec2 z) { // f(z) = z^ - 1
    // return cmul(z,cmul(z,z)) - vec2(iTime,0);
    float a = roots.x;
    float b = roots.y;
    float c = roots.z; 
    return cmul(z,cmul(z,z)) - cmul(z,z)*(a+b+c) - z*(c*(a+b)) - c*a*b;

}
vec2 dfn(vec2 z) { // f'(z) = 3*z^2
    // return cmul(vec2(3,0),cmul(z,z)) + vec2(0,iTime);
    float a = roots.x;
    float b = roots.y;
    float c = roots.z; 
    return 3*cmul(z,z) - 2*z*(a+b+c) - c*(a+b);
}


void main(){
    vec2 uv = 2.0*(gl_FragCoord.xy - iResolution.xy/2)/min(iResolution.x, iResolution.y) ;
    vec2 z = uv;
    vec2 zp = uv;
    float i = 0.0;
    float thresh = 0.0001;
    for(i = 0; i < 100.0; i++) {
        z -= cdiv(fn(z), dfn(z)); // newton fractal
        if(length(z - zp) < thresh) break;
        zp = z;
    }

    float theta = atan(z.y, z.x);
    float rot = mod(theta/(2*PI),1);

    vec3 color;
    if(rot < 0.33){
        color = vec3(0.8941*m_sin(iTime), 0.4745*m_sin(iTime + PI/1.21), 1.0);
    }
    else if(rot < 0.66){
        color = vec3(0.6196*m_sin(iTime+0.123), 0.4431*m_sin(iTime + 0.453 + PI/1.21), 1.0);
    }
    else{
        color = vec3(0.6353, 1.0, 0.8314);
    }
    outColor = vec4(color*(log(i/5)*0.25+0.1),1.0);

}