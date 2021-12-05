#version 330 core

layout (location = 0) in vec3 positionIn;
layout (location = 1) in vec3 normalIn;

out vec3 normal;
out vec3 positionWorld;

uniform mat4 camera;
uniform mat4 model;

void main()
{
  gl_Position = camera * model * vec4(positionIn, 1.0f);
  
  normal = normalIn;
  positionWorld = vec3(model * vec4(positionIn, 1.0f));
}

