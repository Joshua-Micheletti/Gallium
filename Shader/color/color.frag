#version 330 compatibility

in vec3 fragmentColor;

out vec3 color;

void main(){
  color = fragmentColor;
}