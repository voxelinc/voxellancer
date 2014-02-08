#version 330

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform mat4 viewProjection;

uniform float emissiveness;

// cube data
layout(location=0) in vec3 v_vertex;
layout(location=1) in vec3 v_normal;

// instance data
layout(location=2) in vec3 v_position;
layout(location=3) in vec4 v_color;
layout(location=4) in float v_emissiveness;

flat out vec3 f_normal;
out vec3 f_color;
out float f_emissiveness;
out vec3 modelposition;

void main() {
    gl_Position = viewProjection * model * (vec4(v_vertex + v_position, 1.0));

    f_normal = (model * vec4(v_normal, 0.0)).xyz;
    f_color = v_color.rgb;
    f_emissiveness = clamp(emissiveness + v_emissiveness, 0, 1);
    modelposition = v_vertex;
}

