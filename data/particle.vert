#version 330

// Input
layout(location=0) in vec3 v_vertex;
layout(location=1) in vec3 v_normal;

layout(location = 2) in vec3 creationPosition;
layout(location = 3) in vec3 creationEulers;
layout(location = 4) in vec3 creationDirectionalSpeed;
layout(location = 5) in vec3 creationAngularSpeed;
layout(location = 6) in float creationTime;
layout(location = 7) in float deathTime;
layout(location = 8) in float scale;
layout(location = 9) in vec4 color;
layout(location = 10) in float emissiveness;
layout(location = 11) in float directinalDampening;
layout(location = 12) in float angularDampening;

// Output
flat out vec3 f_normal;
flat out float f_remainingLifetime; // there is no bool for out
out vec3 f_color;
out float f_emissiveness;
out vec3 modelposition;


// Uniforms
uniform mat4 viewProjection;
uniform float time;


vec3 qtransform(vec4 q, vec3 v) {
    vec3 QuatVector = vec3(q.x, q.y, q.z);
    vec3 uv = cross(QuatVector, v);
    vec3 uuv = cross(QuatVector, uv);
    uv *= (2 * q.w);
    uuv *= 2;

    return v + uv + uuv;
}

vec4 quat(vec3 euler) {
    vec3 c = cos(euler * 0.5);
    vec3 s = sin(euler * 0.5);

    vec4 q;

    q.w = c.x * c.y * c.z + s.x * s.y * s.z;
    q.x = s.x * c.y * c.z - c.x * s.y * s.z;
    q.y = c.x * s.y * c.z + s.x * c.y * s.z;
    q.z = c.x * c.y * s.z - s.x * s.y * c.z;

    return q;
}

void main() {
	float timeDelta = time - creationTime;

	vec3 particlePosition = (-directinalDampening / 2) * (timeDelta * timeDelta) + creationDirectionalSpeed * timeDelta + creationPosition;
	vec3 particleEulers = (-angularDampening / 2) * (timeDelta * timeDelta) + creationAngularSpeed * timeDelta + creationEulers;
	vec4 particleOrientation = quat(particleEulers);
    f_remainingLifetime = deathTime - time;
	f_color = color.xyz;
    f_emissiveness = emissiveness;
    modelposition = v_vertex;
    f_normal  = v_normal;

    gl_Position = viewProjection * vec4(qtransform(particleOrientation, v_vertex) * scale + particlePosition, 1.0);
}

