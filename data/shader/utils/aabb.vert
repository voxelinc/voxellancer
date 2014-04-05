#version 330


uniform mat4 viewProjection;

layout (location = 0) in vec3 v_vertex;
layout (location = 1) in vec3 v_middle;
layout (location = 2) in vec3 v_extent;

void main() {
    gl_Position = viewProjection * vec4(v_middle + (v_vertex * v_extent), 1.0); 
}

