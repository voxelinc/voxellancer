#version 130

layout(points) in;
layout(line_strip) out;

uniform mat4 viewProjection;
uniform vec4 speed;

in vec4 pos[1];

void main(void) {

    vec4 offset = viewProjection * (speed * 4);

    gl_Position = pos[0] + offset;
    EmitVertex();

    gl_Position = pos[0]- offset;
    EmitVertex();

    EndPrimitive();

}

