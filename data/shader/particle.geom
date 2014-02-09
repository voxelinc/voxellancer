#version 330

layout (triangles) in;
layout (triangle_strip, max_vertices = 3) out;

uniform float time;

layout(location = 0) in vec3 g_normal[];
layout(location = 1) in float g_deathTime[];
layout(location = 2) in vec3 g_color[];
layout(location = 3) in float g_emissiveness[];
layout(location = 4) in vec3 g_modelposition[];

layout(location = 0) flat out vec3 f_normal;
layout(location = 1) out vec3 f_color;
layout(location = 2) out float f_emissiveness;
layout(location = 3) out vec3 f_modelposition;


void main() {
    if(g_deathTime[0] < time) {
        for(int i; i < gl_in.length(); i++) {
            gl_Position = gl_in[i].gl_Position;
            f_normal = g_normal[i];
            f_color = g_color[i];
            f_emissiveness = g_emissiveness[i];
            f_modelposition = g_modelposition[i];
            EmitVertex();
        }

        EndPrimitive();
    }
}
