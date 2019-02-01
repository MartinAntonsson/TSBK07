#version 150

in  vec4 color;
in  vec3 in_Position;

out vec4 colorV;

void main(void)
{
	colorV = color;
	gl_Position = vec4(in_Position, 1.0);
}
