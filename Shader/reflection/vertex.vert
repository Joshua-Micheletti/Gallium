#version 330 core
layout (location = 0) in vec3 vertex ;
layout (location = 2) in vec3 normal ;

out vec3 Normal;
out vec3 Position;
out vec3 cameraPos;

uniform mat4 modelMatrix ;
uniform mat4 viewMatrix ;
uniform mat4 projectionMatrix ;
uniform vec3 eyePosition ;

void main() {
    Normal = mat3(transpose(inverse(modelMatrix))) * normal;
    Position = vec3(modelMatrix * vec4(vertex, 1.0));
    gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(vertex, 1.0);
    cameraPos = eyePosition;
}
