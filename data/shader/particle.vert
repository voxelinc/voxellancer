#version 330

// Input
layout(location = 0) in vec3 v_vertex;
layout(location = 1) in vec3 v_normal;

layout(location = 2) in vec3 creationPosition;
layout(location = 3) in vec3 creationEulers;
layout(location = 4) in vec3 directionalSpeed;
layout(location = 5) in vec3 angularSpeed;
layout(location = 6) in float creationTime;
layout(location = 7) in float deathTime;
layout(location = 8) in float scale;
layout(location = 9) in vec4 color;
layout(location = 10) in float emissiveness;
layout(location = 11) in float directinalDampening;
layout(location = 12) in float angularDampening;

// Output
out vec3 g_normal;
out float g_deathTime;
out vec3 g_color;
out float g_emissiveness;
out vec3 g_modelposition;


// Uniforms
uniform mat4 viewProjection;
uniform float time;

vec3 qtransform(vec4 q, vec3 v);
vec4 quat(vec3 euler);

void main() {
    float timeDelta = time - creationTime;
    g_deathTime = deathTime;

    vec3 particlePosition = directionalSpeed * timeDelta + creationPosition;
    vec3 particleEulers = angularSpeed * timeDelta + creationEulers;
    vec4 particleOrientation = quat(particleEulers);
    g_color = color.xyz;
    g_emissiveness = emissiveness;
    g_modelposition = v_vertex;
    g_normal = qtransform(particleOrientation, v_normal);

    gl_Position = viewProjection * vec4(qtransform(particleOrientation, v_vertex) * scale + particlePosition, 1.0);
}

