#version 330 core

in vec3 position;
in vec3 color;
in vec2 textCoord;

out vec3 ourColor;
out vec2 textureCoord;

void main(){
	gl_Position = vec4(position, 1.0);

	ourColor = color;

	textureCoord = textCoord;
};