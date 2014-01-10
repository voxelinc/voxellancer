#version 130

layout(points) in;

layout(triangle_strip) out;

uniform mat4 viewProjection;
uniform vec4 speed;
uniform float aspectRatio;

in vec4 pos[1];
in float brightness[1];
in float size[1];

out vec2 v_uv;
out float v_brightness;

void main(void) {

    float min_size = 0.5 * size[0];

    vec4 offset = viewProjection * (speed / 10) * size[0];
    offset.y += min_size*aspectRatio;
    vec4 orthogonal = vec4(min_size,0,0,0);

    v_brightness = brightness[0];

    v_uv = vec2(0,0);
    gl_Position = pos[0] + offset + orthogonal;
    EmitVertex();

    v_uv = vec2(0,1);
    gl_Position = pos[0] + offset - orthogonal;
    EmitVertex();

    v_uv = vec2(1,0);
    gl_Position = pos[0] - offset + orthogonal;
    EmitVertex();
    
    v_uv = vec2(1,1);
    gl_Position = pos[0] - offset - orthogonal;
    EmitVertex();

    EndPrimitive();

}

