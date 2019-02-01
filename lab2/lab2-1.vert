#version 150

in vec3 in_Position;
in vec3 in_Normal;
in vec2 inTexCoord;

out vec4 colorV;
out vec2 inTexCoordV;

uniform mat4 RotationY;

void main(void)
{
	inTexCoordV = inTexCoord;
	colorV = RotationY * vec4(in_Normal, 1.0);
	colorV = 0.5 * (colorV + 1);
	gl_Position = RotationY * vec4(in_Position, 1.0);
}
