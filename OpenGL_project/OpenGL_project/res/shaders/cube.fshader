#version 330 core

in vec2 textureCoord;

out vec4 result;

uniform sampler2D ourTexture;

void main(){
	result = texture(ourTexture, textureCoord);	
}