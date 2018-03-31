#version 130
in vec2 vPos;
in vec3 vColor;

out vec4 fColor;

void main()
{
	fColor=vec4(vColor,0.0);
	gl_Position=vec4(vPos,0.0,0.0);
}

