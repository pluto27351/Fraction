varying vec4 v_fragmentColor;
varying vec2 v_texCoord;

void main(void)
{
    vec4 c = texture2D(CC_Texture0, v_texCoord);
    gl_FragColor.xyz = vec3((0.2126*c.r + 0.7152*c.g + 0.0722*c.b)*0.5);  //rbg轉yuv 並取y(亮度)值   *0.5為降低亮度
    gl_FragColor.w =c.w*0.5;
}
