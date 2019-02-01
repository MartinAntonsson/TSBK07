#version 150

in vec4 colorV;
in vec2 inTexCoordV;
in float timeV;

out vec4 out_Color;

void main(void)
{
	float r = sin((inTexCoordV.s + inTexCoordV.t) * 10 * abs(sin(timeV))) / 2 + 0.5;
	float g = sin((3 * inTexCoordV.s - 2 * inTexCoordV.t) * 30 * abs(sin(timeV))) / 2 + 0.5;
	float b = sin((inTexCoordV.t - inTexCoordV.s) * 3 * abs(sin(timeV))) / 2 + 0.5;
	out_Color = vec4(r, g, b, 1.0);
}
