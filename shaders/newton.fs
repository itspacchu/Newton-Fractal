#version 330

#define PI 3.14159265358979323846

uniform vec2 iResolution;
uniform float iTime;
uniform vec3 roots;

uniform vec2 coordMove = vec2(0.12,-0.35);

in vec4 fragColor;


out vec4 outColor;

float m_sin(float t){
    return sin(2*t)*0.5 + 0.5;
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
    vec2 a = vec2(3,3);
    vec2 b = vec2(2.1+0.1*m_sin(iTime/3),-0.62+m_sin(iTime/5.2 + PI/12));
    vec2 c = vec2(2.1+0.1*m_sin(iTime/3),0.62+m_sin(iTime/5.2 + PI/12)); 
    return cmul(z,cmul(z,z)) - cmul(cmul(z,z),(a+b+c)) - cmul(z,cmul(c,(a+b))) - cmul(a,cmul(b,c));

}
vec2 dfn(vec2 z) { // f'(z) = 3*z^2
    // return cmul(vec2(3,0),cmul(z,z)) + vec2(0,iTime);
    vec2 a = vec2(3,3);
    vec2 b = vec2(2.1+0.1*m_sin(iTime/10),-0.62+m_sin(iTime/15.2 + PI/12));
    vec2 c = vec2(2.1+0.1*m_sin(iTime/10),0.62+m_sin(iTime/15.2 + PI/12)); 
    return 3*cmul(z,z) - 2*cmul(z,(a+b+c)) - cmul(c,(a+b));
}


void main(){
    vec2 uv = 2.0*(gl_FragCoord.xy - iResolution.xy/2)/min(iResolution.x, iResolution.y) ;
    highp vec2 z = (uv + coordMove)/(5.0*m_sin(iTime/30 + PI/2));
    highp vec2 zp = z;
    float i = 0.0;
    highp float thresh = 0.00001;
    for(i = 0; i < 50.0; i++) {
        z -= cdiv(fn(z), dfn(z)); // newton fractal
        if(length(z - zp) < thresh) break;
        zp = z;
    }

    float theta = atan(z.y, z.x);
    float rot = mod(theta/(2*PI),1);

    vec3 color;
    if(rot < 0.3){
        color = vec3(0.5255, 0.2588, 0.2588);
    }
    else if(rot < 0.6){
        color = vec3(0.5725, 0.5451, 0.8314);
    }
    else{
        color = vec3(0.4784, 0.7059, 0.5373);
    }

    outColor = vec4(color*(log(i/4)*0.5+0.1),1.0);
}