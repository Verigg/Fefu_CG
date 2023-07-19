#version 330 core

in vec2 TexCoords;
out vec4 OutColor;
uniform sampler2D tex;

void main() {
		vec3 rgb = texture(tex, TexCoords).rgb;
		OutColor = vec4(rgb,0);
}