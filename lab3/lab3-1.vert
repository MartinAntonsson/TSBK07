#version 150

in vec3 in_Position;
in vec3 in_Normal;
in vec2 inTexCoord;

uniform mat4 mtw;
uniform mat4 total;

out vec2 texCoordV;
out vec3 normalV;

void main(void)
{
	texCoordV = inTexCoord;
	normalV = mat3(mtw) * in_Normal;
	gl_Position = total * vec4(in_Position, 1.0);
}
