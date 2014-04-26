#version 330

// Input
layout(location = 0) in vec3 v_vertex;
layout(location = 1) in vec3 v_normal;

layout(location = 2) in vec3 v_gridCell;
layout(location = 3) in vec4 v_color;
layout(location = 4) in float v_emissiveness;

layout(location = 5) in vec3 v_originPosition;
layout(location = 6) in vec3 v_originEulers;
layout(location = 7) in vec3 v_directionalSpeed;
layout(location = 8) in vec3 v_angularSpeed;
layout(location = 9) in vec3 v_center;
layout(location = 10) in float v_originTime;
layout(location = 11) in float v_deathTime;
layout(location = 12) in float v_active;


// Output
out vec4 f_color;
flat out vec3 f_normal;
out float f_emissiveness;
out vec3 f_modelposition;
flat out float f_active;
flat out float f_deathTime;

// Uniforms
uniform mat4 viewProjection;
uniform float time;
uniform float scale;
uniform float emissiveness;


vec3 qtransform(vec4 q, vec3 v);
vec4 quat(vec3 euler);

void main() {
    f_active = v_active;
    f_deathTime = v_deathTime;

    float deltaTime = time - v_originTime;

    f_color = v_color;
    f_normal = v_normal;
    f_emissiveness = clamp(emissiveness + v_emissiveness, 0, 1);
    f_modelposition = v_vertex;

    vec3 bulletEulers = v_originEulers + v_angularSpeed * deltaTime * 0.01;
    vec4 bulletOrientation = quat(bulletEulers);

    vec3 bulletPosition = v_originPosition + v_directionalSpeed * deltaTime;

    gl_Position = viewProjection * vec4(qtransform(bulletOrientation, v_vertex + v_gridCell - v_center) * scale + bulletPosition, 1.0f);
}

