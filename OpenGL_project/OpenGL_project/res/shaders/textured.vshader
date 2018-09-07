#version 330 core

in vec3 position;
in vec3 color;
in vec2 textCoord;

out vec3 ourColor;
out vec2 textureCoord;

uniform mat4 transform;

void main(){
	gl_Position = transform * vec4(position, 1.0);

	ourColor = color;

	textureCoord = textCoord;
};