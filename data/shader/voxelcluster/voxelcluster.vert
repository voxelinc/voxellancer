#version 330

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform mat4 viewProjection;

uniform float emissiveness;

// cube data
layout(location = 0) in vec4 v_vertex;
layout(location = 1) in vec4 v_normal;

// instance data
layout(location = 2) in vec3 v_position;
layout(location = 3) in vec4 v_color;
layout(location = 4) in float v_emissiveness;
layout(location = 5) in uint v_faces;


flat out vec3 f_normal;
flat out vec4 f_color;
out float f_emissiveness;
out vec3 f_modelposition;


void main() {
    // to avoid z-fighting, minimally shrink all cubes
    gl_Position = viewProjection * model * (vec4(v_position.xyz + v_vertex.xyz * 0.999, 1.0));

    f_normal = (model * vec4(v_normal.xyz, 0.0)).xyz * v_color.xyz;
    //if ((v_faces & (uint(0x10000000) >> uint(v_normal.w))) != uint(0x00000000)){ //(0x1 >> uint(v_normal.w))
	//if ((uint(0x2) & (uint(0x1) << uint(v_normal.w))) != uint(0x0)) {
	if (v_faces == uint(2)) {
		f_color = vec4(1.0, 0.0, v_faces, 1.0);
	} else {
		f_color = v_color;
	}
    f_emissiveness = clamp(emissiveness + v_emissiveness, 0, 1);
    f_modelposition = v_vertex.xyz;
}

