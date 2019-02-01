#version 150

in  vec4 color;
in  vec3 in_Position;

out vec4 colorV;

uniform mat4 myMatrix;

void main(void)
{
	colorV = color;
	gl_Position = myMatrix * vec4(in_Position, 1.0);
}
