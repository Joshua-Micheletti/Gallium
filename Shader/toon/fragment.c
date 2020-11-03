#version 330 core

in vec3 color;
in vec3 lightFragment;
in vec3 eyeFragment;
in vec3 worldPosition;
in vec3 worldNormal;

out vec3 outColor;



void main() {
    vec3 lightColor = vec3(1.0, 1.0, 1.0);
    float ambientStrength = 0.2;
    vec3 ambient = ambientStrength * lightColor;

    vec3 L = normalize(lightFragment - worldPosition);
    vec3 V = normalize(eyeFragment - worldPosition);

    float diff = max(dot(worldNormal, L), 0.0);
    vec3 diffuse = diff * lightColor;

    float specularStrength = 1;
    vec3 reflectDir = reflect(-L, worldNormal);

    float spec = pow(max(dot(V, reflectDir), 0.0), 64);

    vec3 specular = specularStrength * spec * lightColor;

    float edgeDetection = (dot(V, worldNormal) > 0.5) ? 1 : 0;

    vec3 light = ambient + diffuse + specular;

    // 2 levels
    // if (light.x > 0.5) {
    //     light = vec3(1);
    // }
    // else {
    //     light = ambient;
    // }

    // 3 levels
    if (light.x > 0.66) {
        light = vec3(1);
    }
    else if (light.x > 0.33) {
        light = vec3(0.66);
    }
    else {
        light = ambient;
    }

    // 4 levels
    // if (light.x > 0.75) {
    //     light = vec3(1);
    // }
    // else if (light.x > 0.5) {
    //     light = vec3(0.75);
    // }
    // else if (light.x > 0.25) {
    //     light = vec3(0.5);
    // }
    // else {
    //     light = ambient;
    // }

    // 8 levels
    // if (light.x > 0.875) {
    //     light = vec3(1);
    // }
    // else if (light.x > 0.75) {
    //     light = vec3(0.875);
    // }
    // else if (light.x > 0.625) {
    //     light = vec3(0.75);
    // }
    // else if (light.x > 0.5) {
    //     light = vec3(0.625);
    // }
    // else if (light.x > 0.375) {
    //     light = vec3(0.5);
    // }
    // else if (light.x > 0.25) {
    //     light = vec3(0.375);
    // }
    // else if (light.x > 0.125) {
    //     light = vec3(0.25);
    // }
    // else {
    //     light = ambient;
    // }

    outColor = light * edgeDetection * color;
}
