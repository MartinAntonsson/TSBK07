#version 150

in vec2 texCoordV;
uniform sampler2D texUnit;

out vec4 out_Color;

void main(void)
{
	out_Color = texture(texUnit, 5 * texCoordV);
}
