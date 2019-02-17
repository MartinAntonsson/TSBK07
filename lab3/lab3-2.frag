#version 150

in vec2 texCoordV;
in vec3 normalV;

uniform sampler2D texUnit;

out vec4 out_Color;

void main(void)
{
	float light = max(0, dot(normalize(vec3(0.58,0.58,0.58)), normalize(normalV)));
	out_Color = light * texture(texUnit, 5 * texCoordV);
}
