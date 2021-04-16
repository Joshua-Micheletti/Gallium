#version 330 core

out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D screenTexture;
uniform sampler2D outlineMask;

float map(float x, float in_min, float in_max, float out_min, float out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

void main() {
    int size = 20;
    int steps = 10;
    ivec2 texSize = textureSize(screenTexture, 0);
    ivec2 newTexCoord = ivec2(TexCoords.x * texSize.x, TexCoords.y * texSize.y);
    vec4 color = vec4(0.0);

    float threshold = 0.01;

    bool hit = false;

    float dist = size + 1;
    float tmpDist;
    if (texelFetch(outlineMask, newTexCoord, 0).x <= 0.5) {
        for (int i = -size; i < size; i += size / steps) {
            for (int j = -size; j < size; j += size / steps) {
                if (texelFetch(outlineMask, ivec2(newTexCoord.x + i, newTexCoord.y + j), 0).x >= 0.5) {
                    tmpDist = sqrt(pow(i, 2) + pow(j, 2));
                    if (tmpDist < dist) {
                        dist = tmpDist;
                    }
                    hit = true;
                } 
            }
        }
    }

    if (hit == true) {
//        FragColor = vec4(1.0, 0.2, 0.0, 1.0);
        FragColor = mix(texelFetch(screenTexture, newTexCoord, 0), vec4(1.0, 0.2, 0.0, 1.0), map(dist, 0, size, 1, 0));
    } else {
        FragColor = texelFetch(screenTexture, newTexCoord, 0);
    }
}
