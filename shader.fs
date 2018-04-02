#version 330

uniform sampler2D tex;

smooth in vec3 fColor;
smooth in vec2 TexCoord;
out vec4 Color;

void main()
{
	Color=texture(tex,TexCoord.st);
}
