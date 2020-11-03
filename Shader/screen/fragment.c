#version 330 core

out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D screenTexture;

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
    // normal colors
    FragColor = vec4(texture(screenTexture, TexCoords).xyz, 1.0);

    // inverted colors
    // FragColor = vec4(vec3(1.0 - texture(screenTexture, TexCoords)), 1.0);

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
    // float aperture = 178.0;
    // float apertureHalf = 0.5 * aperture * (PI / 180.0);
    // float maxFactor = sin(apertureHalf);
    //
    // vec2 uv;
    // vec2 xy = 2.0 * TexCoords - 1.0;
    // float d = length(xy);
    // if (d < (2.0 - maxFactor)) {
    //   d = length(xy * maxFactor);
    //   float z = sqrt(1.0 - d * d);
    //   float r = atan(d, z) / PI;
    //   float phi = atan(xy.y, xy.x);
    //
    //   uv.x = r * cos(phi) + 0.5;
    //   uv.y = r * sin(phi) + 0.5;
    // } else {
    //   uv = TexCoords;
    // }
    //
    // FragColor = vec4(texture(screenTexture, uv).xyz, 1.0);


    // barrel distortion
    // vec2 xy = 2.0 * TexCoords.xy - 1.0;
    // vec2 uv;
    // float d = length(xy);
    //
    // if (d < 1.0) {
    //   uv = Distort(xy);
    // } else {
    //   uv = TexCoords.xy;
    // }
    //
    // FragColor = texture2D(screenTexture, uv);
}
