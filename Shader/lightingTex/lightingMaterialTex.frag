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

uniform sampler2D diffuseTex ;
uniform sampler2D specularTex ;

out vec3 color;

void main() {
  // vec3 lightColor = fragLightColor;
  // float ambientStrength = 0.2;
  // ambient
  // vec3 ambient = ambientStrength * lightColor;
  // vec3 ambient = lightColor * fragAmbient;
  vec3 ambient = fragLightAmbient * fragAmbient * vec3(texture(diffuseTex, uvs)) * 0.3;

  // diffuse
  vec3 norm = normalize(fragNormal);
  vec3 lightDirection = normalize(fragLightPosition - fragPosition);
  float diff = max(dot(norm, lightDirection), 0.0);
  // vec3 diffuse = lightColor * (diff * fragDiffuse);
  vec3 diffuse = fragLightDiffuse * diff * vec3(texture(diffuseTex, uvs)) * fragDiffuse;

  // specular
  // float specularStrength = 1;
  vec3 viewDir = normalize(fragEyePosition - fragPosition);
  vec3 reflectDir = reflect(-lightDirection, norm);
  float spec = pow(max(dot(viewDir, reflectDir), 0.0), fragShininess);
  // vec3 specular = lightColor * (spec * fragSpecular);
  vec3 specular = fragLightSpecular * (spec * fragSpecular * vec3(texture(specularTex, uvs)));

  color = (ambient + diffuse + specular);
  // color = (ambient + diffuse + specular) * vec3(0.1, 0.3, 1.0);
}