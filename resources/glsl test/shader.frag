#ifdef GL_ES
precision mediump float;
#endif

//uniform 
vec3 u_color = vec3(0.4, 0.2, 0.8);

void main() {
    gl_FragColor = vec4(u_color, 1.0);
    
}