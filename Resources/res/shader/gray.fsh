
#ifdef GL_ES
precision mediump float;
#endif

varying vec4 v_fragmentColor;
varying vec2 v_texCoord;

uniform sampler2D u_texture;

void main() {
    vec4 c = texture2D(CC_Texture0, v_texCoord);
    gl_FragColor.xyz = vec3(0.6*c.r + 0.5*c.g + 0.05*c.b);
    gl_FragColor.w = c.w;
}
