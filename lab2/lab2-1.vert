#version 150

in vec3 in_Position;
in vec3 in_Normal;
in vec2 inTexCoord;

out vec4 colorV;
out vec2 inTexCoordV;
out float timeV;

uniform mat4 RotationY;
uniform float time;

void main(void)
{
	timeV = time;
	inTexCoordV = inTexCoord;
	//colorV = RotationY * vec4(normalize(in_Normal), 1.0);
	//colorV = 0.5 * (colorV + 1);
	colorV = vec4(0.6,0.6,0.6,1.0);
	gl_Position = RotationY * vec4(in_Position, 1.0);
}
