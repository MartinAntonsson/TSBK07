#version 150

in vec3 in_Position;
in vec3 in_Normal;
in vec2 inTexCoord;

uniform mat4 rot;
uniform mat4 projCam;

out vec2 texCoordV;
//out float lightV;
out vec3 normalV;

void main(void)
{
	texCoordV = inTexCoord;
	normalV = mat3(rot) * in_Normal;
	//lightV = max(0, normalize(dot(vec3(0.58,0.58,0.58), mat3(rot) * in_Normal)));
	gl_Position = projCam * rot * vec4(in_Position, 1.0);
}
