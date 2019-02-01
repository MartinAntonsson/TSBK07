#version 150

in vec4 colorV;
out vec4 out_Color;

void main(void)
{
	//out_Color = vec4(0.5);
	//out_Color = vec4(0.1,1.0,0.5,1.0);
	out_Color = colorV;
}
