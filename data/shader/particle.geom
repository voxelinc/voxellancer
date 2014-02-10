#version 330

layout (triangles) in;
layout (triangle_strip, max_vertices = 3) out;

uniform float time;

in vec3 g_normal[];
in float g_deathTime[];
in vec3 g_color[];
in float g_emissiveness[];
in vec3 g_modelposition[];

flat out vec3 f_normal;
out vec3 f_color;
out float f_emissiveness;
out vec3 f_modelposition;


void main() {
    if(g_deathTime[0] > time) {
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
