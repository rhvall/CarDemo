varying lowp vec4 colourOUT;
varying mediump vec2 textureOUT;
uniform sampler2D diffuseTex;

void main (void) 
{
    gl_FragColor = texture2D(diffuseTex, textureOUT);
    //gl_FragColor = colourOUT;
}