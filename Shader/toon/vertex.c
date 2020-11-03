#version 330 core

layout (location = 0) in vec3 vertex ;
layout (location = 2) in vec3 normal ;

out vec3 color;
out vec3 lightFragment;
out vec3 eyeFragment;
out vec3 worldPosition;
out vec3 worldNormal;

uniform mat4 modelMatrix ;
uniform mat4 viewMatrix ;
uniform mat4 projectionMatrix ;
uniform vec3 lightPosition ;
uniform vec3 eyePosition ;

void main() {
    gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(vertex, 1);
    color = vec3(1, 1, 1);
    lightFragment = lightPosition;
    eyeFragment = eyePosition;
    worldPosition = vec3(modelMatrix * vec4(vertex, 1.0));
    worldNormal = mat3(transpose(inverse(modelMatrix))) * normal;
}