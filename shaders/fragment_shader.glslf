#version 330 core

in vec3 normal;
in vec3 positionWorld;

out vec4 fragment_color;

uniform vec3 lightPosition;

void main()
{
  vec3 norm = normalize(normal);
  vec3 lightDir = normalize(lightPosition - positionWorld);

  float diffuseComponent = max(dot(norm, lightDir), 0.0);
  vec4 ambient_color = vec4(0.5f, 0.25f, 0.0f, 1.0f);
  fragment_color = ambient_color + diffuseComponent * vec4(0.5f, 0.5f, 0.5f, 1.0f);
}

