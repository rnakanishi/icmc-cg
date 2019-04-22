#version 330 core
out vec4 FragColor;

// uniform vec4 vertexColor; // recebido do codigo principal
in vec4 vertexColor; // recebido do vertex shader

void main() { FragColor = vertexColor; }