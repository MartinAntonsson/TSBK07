#version 150

in vec3 in_Position;
in vec3 in_Normal;
in vec2 inTexCoord;

uniform mat4 rot;
uniform mat4 projCam;

out vec2 texCoordV;

void main(void)
{
	texCoordV = inTexCoord;
	gl_Position = projCam * rot * vec4(in_Position, 1.0);
}
