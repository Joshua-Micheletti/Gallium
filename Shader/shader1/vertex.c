#version 330 core

layout (location = 0) in vec3 vertex ;
layout (location = 1) in vec2 uv ;

out vec2 texcoord;

uniform mat4 modelMatrix ;
uniform mat4 viewMatrix ;
uniform mat4 projectionMatrix ;

void main() {
  gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(vertex, 1);

  texcoord = uv;
}
