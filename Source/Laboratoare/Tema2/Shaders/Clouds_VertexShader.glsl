#version 330

layout(location = 0) in vec3 v_position;
layout(location = 1) in vec3 v_normal;
layout(location = 2) in vec2 v_texture_coord;
layout(location = 3) in vec3 v_color;

// Uniform properties
uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;
uniform vec3 object_color;
uniform float time;

out vec3 color;
out float out_time;

float rand(vec2 co){
    return fract(sin(dot(co.xy ,vec2(12.9898,78.233))) * 43758.5453);
}

void main()
{
	vec3 pos = v_position;
	out_time = time;
	color = object_color;

	
	float random = rand(vec2(time));
	if(random < 100) {
		pos.y -= sin(time);
	}

	pos.z -= 5;
	gl_Position = Projection * View * Model * vec4(pos, 1.0);
}

