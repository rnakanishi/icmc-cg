#version 330 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aColor;

// specify a normal output to the fragment shader
uniform mat4 transform;
out vec4 vertexColor;

void main() {
  gl_Position = transform * vec4(aPos, 1.0f);
  vertexColor = vec4(aColor, 1.0);
}