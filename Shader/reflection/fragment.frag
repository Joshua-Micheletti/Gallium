#version 330 core
out vec4 FragColor;

in vec3 Normal;
in vec3 Position;
in vec3 cameraPos;

uniform samplerCube skybox;

float map(float value, float min1, float max1, float min2, float max2) {
    return min2 + (value - min1) * (max2 - min2) / (max1 - min1);
}

vec4 blur5(sampler2D image, vec2 uv, vec2 resolution, vec2 direction) {
  vec4 color = vec4(0.0);
  vec2 off1 = vec2(1.3333333333333333) * direction;
  color += texture2D(image, uv) * 0.29411764705882354;
  color += texture2D(image, uv + (off1 / resolution)) * 0.35294117647058826;
  color += texture2D(image, uv - (off1 / resolution)) * 0.35294117647058826;
  return color; 
}

void main() {
    vec3 I = normalize(Position - cameraPos);
    vec3 R = reflect(I, normalize(Normal));
    float r = map(255, 0, 255, 0, 1);
    float g = map(255, 0, 255, 0, 1);
    float b = map(255, 0, 255, 0, 1);

    FragColor = vec4(texture(skybox, R).rgb, 1.0) * vec4(r, g, b, 1.0);
}
