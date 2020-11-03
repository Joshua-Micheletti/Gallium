#version 440 compatibility

in vec2 uvs;
in vec3 fragNormal;
in vec3 fragLightPosition;
in vec3 fragPosition;
in vec3 fragEyePosition;

out vec3 color;

uniform sampler2D texture0;

void main() {
  vec3 lightColor = vec3(1.0, 1.0, 1.0);
  float ambientStrength = 0.2;

  vec3 ambient = ambientStrength * lightColor;

  vec3 norm = normalize(fragNormal);
  vec3 lightDirection = normalize(fragLightPosition - fragPosition);

  float diff = max(dot(norm, lightDirection), 0.0);
  vec3 diffuse = diff * lightColor;

  float specularStrength = 1;
  vec3 viewDir = normalize(fragEyePosition - fragPosition);
  vec3 reflectDir = reflect(-lightDirection, norm);

  float spec = pow(max(dot(viewDir, reflectDir), 0.0), 64);

  vec3 specular = specularStrength * spec * lightColor;

  color = (ambient + diffuse + specular) * texture(texture0, uvs).rgb;
  // color = (ambient + diffuse + specular) * vec3(0.1, 0.3, 1.0);
}
