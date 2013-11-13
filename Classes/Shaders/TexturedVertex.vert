uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projMatrix;

attribute vec3 position;
attribute vec4 colour;
attribute vec2 texCoord;
varying vec4 colourOUT;
varying vec2 textureOUT;

void main (void) 
{
    gl_Position = projMatrix * viewMatrix * modelMatrix * vec4(position, 1.0);
    colourOUT = colour;
    textureOUT = texCoord;
}
