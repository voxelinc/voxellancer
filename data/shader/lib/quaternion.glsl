#version 330

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
