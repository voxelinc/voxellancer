#version 130
#extension GL_ARB_draw_instanced : require

in vec3 v_vertex;
in vec3 v_normal;
in vec3 v_position;
in vec4 v_orientation;
in float v_scale;
in vec4 v_color;
in float v_emissiveness;


flat out vec3 f_normal;
out vec3 f_color;
out float f_emissiveness;
out vec3 modelposition;

uniform mat4 viewProjection;

vec3 qtransform(vec4 q, vec3 v) { 
    vec3 QuatVector = vec3(q.x, q.y, q.z);
    vec3 uv = cross(QuatVector, v);
    vec3 uuv = cross(QuatVector, uv);
    uv *= (2 * q.w); 
    uuv *= 2; 

    return v + uv + uuv;
}

void main() {
    gl_Position = viewProjection * vec4(qtransform(v_orientation, v_vertex) * v_scale + v_position, 1.0);
    f_normal = qtransform(v_orientation, v_normal);   
    f_color = v_color.xyz;

    f_emissiveness = v_emissiveness;
    modelposition = v_vertex;
}

