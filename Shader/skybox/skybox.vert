#version 410 core
layout (location = 0) in vec3 vertex ;

out vec3 TexCoords;

uniform mat4 projectionMatrix ;
uniform mat4 viewMatrix ;

void main() {
    TexCoords = vertex;
    gl_Position = projectionMatrix * viewMatrix * vec4(vertex, 1.0);
}
