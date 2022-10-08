#version 330 compatibility

in vec2 uvs;
in vec3 fragNormal;
in vec3 fragLightPosition;
in vec3 fragPosition;
in vec3 fragEyePosition;

in vec3 fragAmbient;
in vec3 fragDiffuse;
in vec3 fragSpecular;
in float fragShininess;

in vec3 fragLightAmbient;
in vec3 fragLightDiffuse;
in vec3 fragLightSpecular;

out vec3 color;

float map(float value, float min1, float max1, float min2, float max2) {
  return min2 + (value - min1) * (max2 - min2) / (max1 - min1);
}

void main() {
  vec3 ambient = fragLightAmbient * fragAmbient * 0.3;

  // diffuse
  vec3 norm = normalize(fragNormal);
  vec3 lightDirection = normalize(fragLightPosition - fragPosition);
  float diff = max(dot(norm, lightDirection), 0.0);
  // vec3 diffuse = lightColor * (diff * fragDiffuse);
  vec3 diffuse = fragLightDiffuse * (diff * fragDiffuse);

  // specular
  // float specularStrength = 1;
  vec3 viewDir = normalize(fragEyePosition - fragPosition);
  vec3 reflectDir = reflect(-lightDirection, norm);
  float spec = pow(max(dot(viewDir, reflectDir), 0.0), fragShininess);
  // vec3 specular = lightColor * (spec * fragSpecular);
  vec3 specular = fragLightSpecular * (spec * fragSpecular);

  color = (ambient + diffuse + specular);
  // outColor = min(max(trueDistance, 0), 1) * color;
  // outColor = vec3(clamp(trueDistance, 0, 1), clamp(trueDistance, 0, 1), clamp(trueDistance, 0, 1));
  // outColor = color;
}
