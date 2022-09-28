#version 330 core

layout (location = 0) in vec3 vertex ;

out vec3 fragmentColor;

uniform mat4 modelMatrix ;
uniform mat4 viewMatrix ;
uniform mat4 projectionMatrix ;
uniform vec3 color ;

float map(float value, float min1, float max1, float min2, float max2) {
  return min2 + (value - min1) * (max2 - min2) / (max1 - min1);
}

void main() {
  gl_Position =  projectionMatrix * viewMatrix * modelMatrix * vec4(vertex, 1);

  // fragmentColor = vec3(map(gl_Position.z, 2, 0, 0.1f, 1), map(gl_Position.z, 5, 0, 0.1f, 1), map(gl_Position.z, 8, 0, 0.1f, 1));
  fragmentColor = color;
}
