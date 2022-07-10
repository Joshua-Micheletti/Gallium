#version 330 compatibility

layout (location = 0) in vec3 vertex ;
layout (location = 1) in vec2 uv ;
layout (location = 2) in vec3 normal ;

out vec2 uvs;
out vec3 fragNormal;
out vec3 fragLightPosition;
out vec3 fragPosition;
out vec3 fragEyePosition;

uniform mat4 modelMatrix ;
uniform mat4 viewMatrix ;
uniform mat4 projectionMatrix ;
uniform vec3 lightPosition ;
uniform vec3 eyePosition ;

void main() {
  gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(vertex, 1);

  uvs = uv;

  fragNormal = mat3(transpose(inverse(modelMatrix))) * normal;

  // fragNormal = normal;

  fragLightPosition = lightPosition;

  fragPosition = vec3(modelMatrix * vec4(vertex, 1.0));

  fragEyePosition = eyePosition;
}
