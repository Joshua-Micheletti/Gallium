#version 330 core

out vec4 FragColor;
  
in vec2 TexCoords;

uniform sampler2D screenTexture;

void main() { 
//	ivec2 texSize = textureSize(screenTexture, 0);
//    ivec2 newTexCoord = ivec2(TexCoords.x * texSize.x, TexCoords.y * texSize.y);
//    vec4 color = vec4(0.0);
//    for (int i = 0; i < 16; i++) {
//        color += texelFetch(screenTexture, newTexCoord, i);
//    }

//    color /= float(16);

//    FragColor = color;

//	FragColor = texelFetch(screenTexture, newTexCoord, 0);
	
    FragColor = vec4(texture(screenTexture, TexCoords).xyz, 1.0);
}