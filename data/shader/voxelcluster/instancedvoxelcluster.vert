#version 330

uniform mat4 view;
uniform mat4 projection;
uniform mat4 viewProjection;

uniform float emissiveness;

// cube data
layout(location = 0) in vec3 v_vertex;
layout(location = 1) in vec3 v_normal;

// instance data
layout(location = 2) in vec3 v_position;
layout(location = 3) in vec4 v_color;
layout(location = 4) in float v_emissiveness;

//worldobject data
layout(location = 5) in vec3 m_position;
layout(location = 6) in vec4 m_orientation;
layout(location = 7) in float m_scale;
layout(location = 8) in vec3 m_center;

flat out vec3 f_normal;
out vec3 f_color;
out float f_emissiveness;
out vec3 f_modelposition;

vec3 qtransform(vec4 q, vec3 v);

void main() {
    // same as Transform::applyTo()
    vec3 position = m_position + qtransform(m_orientation, (m_scale * (-m_center + v_vertex + v_position)));

    gl_Position = viewProjection * vec4(position, 1.0);

    f_normal = vec4(qtransform(m_orientation, v_normal), 0.0)).xyz;
    f_color = v_color.rgb;
    f_emissiveness = clamp(emissiveness + v_emissiveness, 0, 1);
    f_modelposition = v_vertex;
}

