#version 330 core

in vec3 normal;
in vec3 positionWorld;

out vec4 fragmentColor;

uniform vec4 color;
uniform vec3 lightPosition;
uniform float diffuseStrength;

void main()
{
  vec3 norm = normalize(normal);
  vec3 lightDir = normalize(lightPosition - positionWorld);
  float diffuseComponent = max(dot(norm, lightDir), 0.0);
  
  fragmentColor = color + diffuseStrength * diffuseComponent * color;
}

