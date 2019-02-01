#version 150

in  vec4 color;
in  vec3 in_Position;

out vec4 colorV;

uniform mat4 myMatrix;

void main(void)
{
	colorV = vec4(1,1,1,0) + vec4(in_Position, 1.0);
	colorV.xyz = 0.5 * colorV.xyz;
	gl_Position = myMatrix * vec4(in_Position, 2.0);
}
