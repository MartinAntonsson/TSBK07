#version 150

in vec2 texCoordV;
uniform sampler2D texUnit;

out vec4 out_Color;

void main(void)
{
	float s = 5;
	float t = 5;
	out_Color = texture(texUnit, vec2(s * texCoordV.s, t * texCoordV.t));
}
