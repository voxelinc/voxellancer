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


flat out vec3 f_normal;
out vec4 f_color;
out float f_emissiveness;
out vec3 f_modelposition;


void main() {
    // to avoid z-fighting, minimally shrink all cubes
    gl_Position = viewProjection * model * (vec4(v_position.xyz + v_vertex.xyz * 0.999, 1.0));

    f_normal = (model * vec4(v_normal.xyz, 0.0)).xyz;
    f_color = v_color;
    f_emissiveness = clamp(emissiveness + v_emissiveness, 0, 1);
    f_modelposition = v_vertex.xyz;
}

