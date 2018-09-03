#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;
layout (location = 2) in vec3 textCoord;

out vec3 ourColor;
out vec3 textureCoord;

void main(){
	gl_Position = vec4(position, 1.0);
	ourColor = color;

	textureCoord = vec2(textCoord.x, 1.0 - textCoord.y);
};