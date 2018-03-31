#version 330

in vec2 vPos;
in vec3 vColor;

smooth out vec3 fColor;

void main()
{
	fColor=vColor;
	gl_Position=vec4(vPos,0,1);
}

