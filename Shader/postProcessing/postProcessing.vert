#version 330 core
layout (location = 0) in vec2 vertex ;
layout (location = 1) in vec2 uv ;

out vec2 TexCoords;

void main() {
    gl_Position = vec4(vertex.x, vertex.y, 0.0, 1.0); 
    TexCoords = uv;
}  