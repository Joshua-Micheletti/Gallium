#version 430 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoords;

uniform float frames;
uniform float denoise;

out vec2 TexCoords;
out float frag_frames;
out float fragDenoise;

	
void main()
{
    TexCoords = aTexCoords;
    frag_frames = frames;
    fragDenoise = denoise;
    gl_Position = vec4(aPos, 1.0);
}