#version 330 core

out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D screenTexture;
uniform sampler2D outlineMask;


float map(float x, float in_min, float in_max, float out_min, float out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}


void main() {
    int size = 5;
    ivec2 texSize = textureSize(screenTexture, 0);
    ivec2 newTexCoord = ivec2(TexCoords.x * texSize.x, TexCoords.y * texSize.y);
    vec4 color = vec4(0.0);

    float threshold = 0.01;

    bool hit = false;

    if (texelFetch(outlineMask, newTexCoord, 0).x <= 0.5) {
        for (int i = -size; i < size && !hit; i++) {
            for (int j = -size; j < size && !hit; j++) {
                float dist = sqrt(pow(i, 2) + pow(j, 2));
                if (dist <= size + size * threshold && dist >= size - size * threshold) {
                    if (texelFetch(outlineMask, ivec2(newTexCoord.x + i, newTexCoord.y + j), 0).x >= 0.5) {
                        hit = true;
                    }
                }   
            }
        }
    }

    if (hit == true) {
//        FragColor = vec4(1.0, 0.2, 0.0, 1.0);
        float r = map(209, 0, 255, 0, 1);
        float g = map(154, 0, 255, 0, 1);
        float b = map(102, 0, 255, 0, 1);
//        FragColor = vec4(1.0, 0.2, 0.0, 1.0);
        FragColor = vec4(r, g, b, 1.0);
        
    } else {
        FragColor = texelFetch(screenTexture, newTexCoord, 0);
    }
}
