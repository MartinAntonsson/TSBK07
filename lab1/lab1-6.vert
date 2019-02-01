#version 150

in  vec3 in_Position;
in  vec3 in_Normal;

out vec4 colorV;

uniform mat4 myMatrix;

void main(void)
{
	colorV = vec4(1,1,1,0) + vec4(in_Normal, 1.0);
	colorV.xyzw = 0.5 * colorV.xyzw;
	//colorV = myMatrix * colorV;
	gl_Position = myMatrix * vec4(in_Position, 1.0);
}
