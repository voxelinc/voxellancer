#version 150

layout(points) in;

layout(triangle_strip, max_vertices=12) out;

in vec4 g_pos[1];
in vec4 g_oldPos[1];
in float g_brightness[1];
in float g_size[1];

out vec2 f_uv;
out float f_brightness;

const float sizeFactor = 0.1;

void main(void) {
    float size = g_size[0] * sizeFactor;
    vec4 pos = g_pos[0];
    vec4 oldPos = g_oldPos[0];

    vec4 dir = pos - oldPos;
    if (length(dir) < 0.0001) {
        dir = vec4(1,0,1,0);
    }

    dir = normalize(dir) * size;

    vec4 orthogonal = normalize(vec4(0,1,0,0)) * size;

    f_brightness = g_brightness[0];

    f_uv = vec2(0,0.5);
    gl_Position = pos - orthogonal;
    EmitVertex();

    f_uv = vec2(0,1);
    gl_Position = pos - orthogonal + dir;
    EmitVertex();

    f_uv = vec2(1,0.5);
    gl_Position = pos + orthogonal;
    EmitVertex();
    
    f_uv = vec2(1,1);
    gl_Position = pos + orthogonal + dir;
    EmitVertex();

    EndPrimitive();

    f_uv = vec2(0,0.5);
    gl_Position = pos - orthogonal;
    EmitVertex();

    f_uv = vec2(0,0.5);
    gl_Position = oldPos - orthogonal;
    EmitVertex();

    f_uv = vec2(1,0.5);
    gl_Position = pos + orthogonal;
    EmitVertex();
    
    f_uv = vec2(1,0.5);
    gl_Position = oldPos + orthogonal;
    EmitVertex();

    EndPrimitive();

    f_uv = vec2(0,0.5);
    gl_Position = oldPos - orthogonal;
    EmitVertex();

    f_uv = vec2(0,0);
    gl_Position = oldPos - orthogonal - dir;
    EmitVertex();

    f_uv = vec2(1,0.5);
    gl_Position = oldPos + orthogonal;
    EmitVertex();
    
    f_uv = vec2(1,0);
    gl_Position = oldPos + orthogonal - dir;
    EmitVertex();

    EndPrimitive();
}

