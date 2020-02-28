#version 330

// TODO: get color value from vertex shader

layout(location = 0) out vec4 out_color;
in vec3 color;
in float out_time;

void main()
{
	out_color = vec4(color, 1);
}