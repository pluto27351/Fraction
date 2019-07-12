
#ifdef GL_ES
precision mediump float;
#endif

varying vec4 v_fragmentColor;
varying vec2 v_texCoord;

uniform sampler2D u_texture;

void main() {
    gl_FragColor = texture2D(CC_Texture0, v_texCoord);
}
