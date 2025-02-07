#version 410

void main() {
    //gl_FragColor = vec4( 0.0, 0.5, 0.75, 1.0 );
    vec2 st = gl_FragCoord.xy/vec2(800, 600);
    gl_FragColor = vec4(st.x, st.y, 1.0, 1.0);
}
