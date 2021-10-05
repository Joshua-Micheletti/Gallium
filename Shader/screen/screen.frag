#version 330 core

out vec4 FragColor;

in vec2 TexCoords;
flat in int fragSamples;

uniform sampler2DMS screenTexture;
uniform int kernelSize_f ;
uniform float kernel_f[121] ;
uniform int effect ;

const float PI = 3.1415926535;

const float BarrelPower = 1.5;

float map(float value, float min1, float max1, float min2, float max2) {
  return min2 + (value - min1) * (max2 - min2) / (max1 - min1);
}

vec2 Distort(vec2 p) {
    float theta  = atan(p.y, p.x);
    float radius = length(p);
    radius = pow(radius, BarrelPower);
    p.x = radius * cos(theta);
    p.y = radius * sin(theta);
    return 0.5 * (p + 1.0);
}

void main() {
    ivec2 texSize = textureSize(screenTexture);

    // MSAA
    if (effect == 0) {
        ivec2 texSize = textureSize(screenTexture);
        ivec2 newTexCoord = ivec2(TexCoords.x * texSize.x, TexCoords.y * texSize.y);
        vec4 color = vec4(0.0);
        for (int i = 0; i < fragSamples; i++) {
            color += texelFetch(screenTexture, newTexCoord, i);
        }

        color /= float(fragSamples);

        FragColor = color;
    }

    // inverted colors
    else if (effect == 1) {
        vec3 texel = texelFetch(screenTexture, ivec2(TexCoords.x * texSize.x, TexCoords.y * texSize.y), 0).xyz;
        FragColor = vec4(1.0 - texel, 1.0);
    }
     
    // color filter
    else if (effect == 2) {
        vec3 texel = texelFetch(screenTexture, ivec2(TexCoords.x * texSize.x, TexCoords.y * texSize.y), 0).xyz;
        FragColor = vec4(texel * vec3(1.0, 0.0, 1.0), 1.0);
    }

    // black circle (view coords)
    else if (effect == 3) {
        float dist;
        vec3 texel = texelFetch(screenTexture, ivec2(TexCoords.x * texSize.x, TexCoords.y * texSize.y), 0).xyz;
        dist = sqrt(pow(TexCoords.x - 0.5, 2) + pow(TexCoords.y - 0.5, 2));
        if (dist > 0.5) {
            FragColor = vec4(0.0, 0.0, 0.0, 1.0);
        } else {
            FragColor = vec4(texel, 1.0);
        }
    }
    
    // black circle (screen coords)
    else if (effect == 4) {
        vec3 texel = texelFetch(screenTexture, ivec2(TexCoords.x * texSize.x, TexCoords.y * texSize.y), 0).xyz;
        float screenX = map(TexCoords.x, 0.0, 1.0, 0.0, 1920.0);
        float screenY = map(TexCoords.y, 0.0, 1.0, 0.0, 1080.0);
        float screenDist = sqrt(pow(screenX - 960, 2) + pow(screenY - 540, 2));
    
        if (screenDist > 500) {
            FragColor = vec4(0.0, 0.0, 0.0, 1.0);
        } else {
            FragColor = vec4(texel, 1.0);
        }
    }

    // black fade (view coords)
    else if (effect == 5) {
        vec3 texel = texelFetch(screenTexture, ivec2(TexCoords.x * texSize.x, TexCoords.y * texSize.y), 0).xyz;
        float dist;
        dist = sqrt(pow(TexCoords.x - 0.5, 2) + pow(TexCoords.y - 0.5, 2));
        FragColor = vec4(texel * (1 - dist), 1.0);
    }  

    // black fade (screen coords)
    else if (effect == 6) {
        vec3 texel = texelFetch(screenTexture, ivec2(TexCoords.x * texSize.x, TexCoords.y * texSize.y), 0).xyz;
        float screenX = map(TexCoords.x, 0.0, 1.0, 0.0, 1920.0);
        float screenY = map(TexCoords.y, 0.0, 1.0, 0.0, 1080.0);
        float screenDist = sqrt(pow(screenX - 960, 2) + pow(screenY - 540, 2));
    
        float distColor = map(screenDist, 0.0, 800.0, 0.0, 1.0);
        FragColor = vec4(texel * (1 - distColor), 1.0);
    }

    // fish eye
    else if (effect == 7) {
        float aperture = 178.0;
        float apertureHalf = 0.5 * aperture * (PI / 180.0);
        float maxFactor = sin(apertureHalf);
    
        vec2 uv;
        vec2 xy = 2.0 * TexCoords - 1.0;
        float d = length(xy);
        if (d < (2.0 - maxFactor)) {
            d = length(xy * maxFactor);
            float z = sqrt(1.0 - d * d);
            float r = atan(d, z) / PI;
            float phi = atan(xy.y, xy.x);
    
            uv.x = r * cos(phi) + 0.5;
            uv.y = r * sin(phi) + 0.5;
        } else {
            uv = TexCoords;
        }
    
        FragColor = vec4(texelFetch(screenTexture, ivec2(uv.x * texSize.x, uv.y * texSize.y), 0).xyz, 1.0);
    }

    //barrel distortion
    else if (effect == 8) {
        vec2 xy = 2.0 * TexCoords.xy - 1.0;
        vec2 uv;
        float d = length(xy);
    
        if (d < 1.0) {
            uv = Distort(xy);
        } else {
            uv = TexCoords.xy;
        }
    
        FragColor = vec4(texelFetch(screenTexture, ivec2(uv.x * texSize.x, uv.y * texSize.y), 0).xyz, 0.0);
     }

    // kernel convolution
    else if (effect == 9) {
        vec3 col = vec3(0.0);

        int j = -int(trunc(float(kernelSize_f) / 2.0));
        int i = -int(trunc(float(kernelSize_f) / 2.0));

        for (int k = 0 ; k < kernelSize_f * kernelSize_f; k++) {
            col += texelFetch(screenTexture, ivec2(TexCoords.x * texSize.x + i, TexCoords.y * texSize.y + j), 0).xyz * kernel_f[k];

            i++;
            if (i > int(trunc(float(kernelSize_f) / 2.0))) {
                i = -int(trunc(float(kernelSize_f) / 2.0));
                j++;
            }
        }

        FragColor = vec4(col, 1.0);
    }
}
