#version 150

in vec3 in_Position;
in vec3 in_Normal;
in vec2 inTexCoord;

uniform mat4 rot;
uniform mat4 projTrans;

out vec2 texCoordV;

void main(void)
{
	texCoordV = inTexCoord;
	gl_Position = projTrans * rot * vec4(in_Position, 1.0);
}
