#version 330

layout (location = 0) in vec3 vertex ;
layout (location = 1) in vec3 color ;

out vec3 fragmentColor;

uniform mat4 modelMatrix ;
uniform mat4 viewMatrix ;
uniform mat4 projectionMatrix ;

void main() {
  gl_Position =  projectionMatrix * viewMatrix * modelMatrix * vec4(vertex, 1);

  fragmentColor = color;
}