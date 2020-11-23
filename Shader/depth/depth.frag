#version 330 core

out vec4 FragColor;

in vec2 TexCoords;
flat in int fragSamples;

uniform sampler2DMS screenTexture;

void main() {
    float zNear = 0.1;
    float zFar = 100.0;

    ivec2 texSize = textureSize(screenTexture);
    ivec2 newTexCoord = ivec2(TexCoords.x * texSize.x, TexCoords.y * texSize.y);

    float color = 0.0;

    for (int i = 0; i < fragSamples; i++) {
        color += texelFetch(screenTexture, newTexCoord, i).x;
    }

    color /= float(fragSamples);

    float linearColor = (2.0 * zNear) / (zFar + zNear - color * (zFar - zNear));
    FragColor = vec4(linearColor, linearColor, linearColor, 1.0);
}