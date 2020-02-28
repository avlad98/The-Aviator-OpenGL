#version 330

layout(location = 0) in vec3 v_position;
layout(location = 1) in vec3 v_normal;
layout(location = 2) in vec2 v_texture_coord;

// Uniform properties
uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;
uniform float time;

out vec3 color;
out float out_time;

float rand(vec2 co){
	return fract(sin(dot(co.xy ,vec2(12.9898,78.233))) * 43758.5453);
}

float rn(float xx){         
    float x0=floor(xx);
    float x1=x0+1;
    float v0 = fract(sin (x0*.014686)*31718.927+x0);
    float v1 = fract(sin (x1*.014686)*31718.927+x1);          

    return (v0*(1-fract(xx))+v1*(fract(xx)))*2-1*sin(xx);
}

void main()
{

	vec3 water_color = vec3(0.05, 0.6, 0.85);
	vec3 new_pos = v_position;
	vec3 brightness = vec3(0);

	
	if(rn(v_normal.x) > 0.2 && v_normal.x < 0.6) {
	float sinus = sin(mod(time, 360))  * -0.04;
		new_pos.x += v_normal.x * 0.04;

		if(abs(sinus) < 0.5){
			new_pos.x += sinus  * -0.04;
		}
	}

	if(rn(v_normal.y) > 0.3 && v_normal.y < 0.6) {
		float cosinus = cos(mod(time, 90));
		new_pos.y += v_normal.y * 0.04;

		if(abs(cosinus) < 0.5) {
			new_pos.y += cosinus * 0.005;
		}
	}

	if(v_normal.x > 0.7 || v_normal.y > 0.7) {
		brightness = vec3(0, 0.05, 0.05);
	} else {
		brightness = vec3(0, -0.05, -0.1);
	}

	if(v_normal.x > 0.8 || v_normal.y > 0.8) {
		brightness = vec3(0, 0.1, 0.15);
	}
	color = water_color + brightness;

		
	gl_Position = Projection * View * Model * vec4(new_pos, 1.0);
}

