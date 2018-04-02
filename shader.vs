#version 330

in vec2 vPos;
in vec2 texCoord;

smooth out vec2 TexCoord;

void main()
{
	gl_Position=vec4(-1+vPos.x/200,-1+vPos.y/300,0,1);
	TexCoord=texCoord;
}

