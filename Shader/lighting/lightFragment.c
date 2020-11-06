#version 440 compatibility

in vec2 uvs;
in vec3 fragNormal;
in vec3 fragLightPosition;
in vec3 fragPosition;
in vec3 fragEyePosition;

out vec3 outColor;

uniform sampler2D texture0;

float map(float value, float min1, float max1, float min2, float max2) {
  return min2 + (value - min1) * (max2 - min2) / (max1 - min1);
}

void main() {
  vec3 lightColor = vec3(1.0, 1.0, 1.0);
  float ambientStrength = 0.2;

  vec3 ambient = ambientStrength * lightColor;

  vec3 norm = normalize(fragNormal);
  vec3 lightDirection = normalize(fragLightPosition - fragPosition);

  vec3 lightDistance = fragLightPosition - fragPosition;

  float distance = distance(fragLightPosition, fragPosition);

  float trueDistance = map(distance, 100, 0, 0, 1);

  float diff = max(dot(norm, lightDirection), 0.0);
  vec3 diffuse = diff * lightColor;

  float specularStrength = 1;
  vec3 viewDir = normalize(fragEyePosition - fragPosition);
  vec3 reflectDir = reflect(-lightDirection, norm);

  float spec = pow(max(dot(viewDir, reflectDir), 0.0), 64);

  vec3 specular = specularStrength * spec * lightColor;

  // color = (ambient + diffuse) * texture(texture0, uvs).rgb;
  vec3 color = (ambient + diffuse + specular) * vec3(1, 1, 1);
  // outColor = min(max(trueDistance, 0), 1) * color;
  // outColor = vec3(clamp(trueDistance, 0, 1), clamp(trueDistance, 0, 1), clamp(trueDistance, 0, 1));
  outColor = color;
}
