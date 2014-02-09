#version 330

layout (triangles) in;
layout (triangle_strip, max_vertices = 3) out;

flat in vec3 g_normal[3];
flat in float g_remainingLifetime[3];
in vec3 g_color[3];
in float g_emissiveness[3];
in vec3 g_modelposition[3];

flat out vec3 f_normal;
out vec3 f_color;
out float f_emissiveness;
out vec3 modelposition;


void main() {
    if(g_remainingLifetime[0] >= 0) {
        for(int i; i < gl_in.length(); i++) {
            gl_Position = gl_in[i].gl_Position;
            f_normal = g_normal[i];
            f_color = g_color[i];
            f_emissiveness = g_emissiveness[i];
            modelposition = g_modelposition[i];
            EmitVertex();
        }

        EndPrimitive();
    }
}
