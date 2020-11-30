#version 330 core

out vec4 FragColor;

in vec2 TexCoords;
flat in int fragSamples;

uniform sampler2DMS screenTexture;
uniform sampler2DMS outlineMask;

void main() {
    int size = 5;
    ivec2 texSize = textureSize(screenTexture);
    ivec2 newTexCoord = ivec2(TexCoords.x * texSize.x, TexCoords.y * texSize.y);
    vec4 color = vec4(0.0);

    float threshold = 0.005;

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
        FragColor = vec4(1.0, 0.2, 0.0, 1.0);
    } else {
        for (int i = 0; i < fragSamples; i++) {
            color += texelFetch(screenTexture, newTexCoord, i);
        }
        color /= float(fragSamples);

        FragColor = color;
    }
}
