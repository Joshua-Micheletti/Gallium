#version 330 core

out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D screenTexture;

const float PI = 3.1415926535;
const float E = 2.71828;

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

const float offset = 1.0 / 961.0;

const int size = 5;

float gaussian(float x, float sigma, float mu) {
    return((1.0 / sigma * sqrt(2 * PI)) * pow(E, (-(1.0f / 2.0f)) * pow((x - mu) / sigma, 2)));
}

void createGaussianKernel(inout float kernel[size * size]) {
    int index = 0;
    float total = 0;
    for (int i = -int(size / 2); i <= int(size / 2); i++) {
        for (int j = -int(size / 2); j <= int(size / 2); j++) {
            kernel[index] = (gaussian(i, 1, 0)) * (gaussian(j, 1, 0));
            total += kernel[index];
            index++;
        }
    }
    index = 0;

    for (int i = -int(size / 2); i <= int(size / 2); i++) {
        for (int j = -int(size / 2); j <= int(size / 2); j++) {
            kernel[index] /= total;
            index++;
        }
    }
}

void main() {
    // normal colors
    FragColor = vec4(texture(screenTexture, TexCoords).xyz, 1.0);

    // inverted colors
//    FragColor = vec4(vec3(1.0 - texture(screenTexture, TexCoords)), 1.0);

    // color filter
    // FragColor = vec4(texture(screenTexture, TexCoords).xyz * vec3(0.8, 0.8, 0.8), 1.0);


    // black circle (view coords)
    // float dist;
    //
    // dist = sqrt(pow(TexCoords.x - 0.5, 2) + pow(TexCoords.y - 0.5, 2));
    // if (dist > 0.5) {
    //   FragColor = vec4(0.0, 0.0, 0.0, 1.0);
    // } else {
    //   FragColor = vec4(texture(screenTexture, TexCoords).xyz, 1.0);
    // }

    // black circle (screen coords)
    // float screenX = map(TexCoords.x, 0.0, 1.0, 0.0, 1920.0);
    // float screenY = map(TexCoords.y, 0.0, 1.0, 0.0, 1080.0);
    // float screenDist = sqrt(pow(screenX - 960, 2) + pow(screenY - 540, 2));
    //
    // if (screenDist > 500) {
    //   FragColor = vec4(0.0, 0.0, 0.0, 1.0);
    // } else {
    //   FragColor = vec4(texture(screenTexture, TexCoords).xyz, 1.0);
    // }


    // black fade (view coords)
    // float dist;
    // dist = sqrt(pow(TexCoords.x - 0.5, 2) + pow(TexCoords.y - 0.5, 2));
    // FragColor = vec4(texture(screenTexture, TexCoords).xyz * (1 - dist), 1.0);

    // black fade (screen coords)
    // float screenX = map(TexCoords.x, 0.0, 1.0, 0.0, 1920.0);
    // float screenY = map(TexCoords.y, 0.0, 1.0, 0.0, 1080.0);
    // float screenDist = sqrt(pow(screenX - 960, 2) + pow(screenY - 540, 2));
    //
    // float distColor = map(screenDist, 0.0, 800.0, 0.0, 1.0);
    // FragColor = vec4(texture(screenTexture, TexCoords).xyz * (1 - distColor), 1.0);

    // fish eye
//    float aperture = 178.0;
//    float apertureHalf = 0.5 * aperture * (PI / 180.0);
//    float maxFactor = sin(apertureHalf);
//    
//    vec2 uv;
//    vec2 xy = 2.0 * TexCoords - 1.0;
//    float d = length(xy);
//    if (d < (2.0 - maxFactor)) {
//        d = length(xy * maxFactor);
//        float z = sqrt(1.0 - d * d);
//        float r = atan(d, z) / PI;
//        float phi = atan(xy.y, xy.x);
//    
//        uv.x = r * cos(phi) + 0.5;
//        uv.y = r * sin(phi) + 0.5;
//    } else {
//        uv = TexCoords;
//    }
//    
//     FragColor = vec4(texture(screenTexture, uv).xyz, 1.0);


     //barrel distortion
//     vec2 xy = 2.0 * TexCoords.xy - 1.0;
//     vec2 uv;
//     float d = length(xy);
//    
//     if (d < 1.0) {
//       uv = Distort(xy);
//     } else {
//       uv = TexCoords.xy;
//     }
//    
//     FragColor = texture2D(screenTexture, uv);

//    vec2 offsets[9] = vec2[](
//        vec2(-offset,  offset), // top-left
//        vec2( 0.0f,    offset), // top-center
//        vec2( offset,  offset), // top-right
//        vec2(-offset,  0.0f),   // center-left
//        vec2( 0.0f,    0.0f),   // center-center
//        vec2( offset,  0.0f),   // center-right
//        vec2(-offset, -offset), // bottom-left
//        vec2( 0.0f,   -offset), // bottom-center
//        vec2( offset, -offset)  // bottom-right    
//    );

    int middle = int(size / 2);
    vec2 offsets[size * size];
    int index = 0;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            offsets[index] = vec2(-middle * offset + offset * j, -middle * offset + offset * i);
            index++;
        }
    }

//    float kernel[9] = float[](
//        1.0/16.0, 2.0/16.0, 1.0/16.0,
//        2.0/16.0, 4.0/16.0, 2.0/16.0,
//        1.0/16.0, 2.0/16.0, 1.0/16.0
//    );

//    float kernel[25] = float[](
//        1/273.0,  4/273.0,  7/273.0,  4/273.0, 1/273.0,
//        4/273.0, 16/273.0, 26/273.0, 16/273.0, 4/273.0,
//        7/273.0, 26/273.0, 41/273.0, 26/273.0, 7/273.0,
//        4/273.0, 16/273.0, 26/273.0, 16/273.0, 4/273.0,
//        1/273.0,  4/273.0,  7/273.0,  4/273.0, 1/273.0
//    );

    float kernel[size * size];
////
    for (int i = 0; i < size * size; i++) {
        kernel[i] = 0;
    }
//
    createGaussianKernel(kernel);

//    float kernel[9] = float[](
//        2,   2, 2,
//        2, -15, 2,
//        2,   2, 2
//    );

//    float kernel[9] = float[](
//        1, 1, 1,
//        1, -8, 1,
//        1, 1, 1
//    );
    
    vec3 sampleTex[size * size];
    for(int i = 0; i < size * size; i++) {
        sampleTex[i] = vec3(texture(screenTexture, TexCoords.st + offsets[i]));
    }

    vec3 col = vec3(0.0);
    for(int i = 0; i < size * size; i++)
        col += sampleTex[i] * kernel[i];
    
//    FragColor = vec4(col, 1.0);
}
