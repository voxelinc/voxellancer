#version 330

uniform ivec2 viewport;
uniform sampler2D source;
uniform vec2 direction;

const int gaussRadius = 11;
const float gaussFilter[gaussRadius] = float[gaussRadius](
    0.0402,0.0623,0.0877,0.1120,0.1297,0.1362,0.1297,0.1120,0.0877,0.0623,0.0402
);

in vec2 v_uv;

layout(location=0) out vec4 fragColor;

void main() {
    vec2 shift = direction * 1/viewport;
    vec2 texCoord = v_uv - floor(gaussRadius/2.0) * shift;
    vec3 color = vec3(0);
    for (int i=0; i<gaussRadius; ++i) {
        color += gaussFilter[i] * 1.5 * texture(source, texCoord).xyz;
        texCoord += shift;
    }
    fragColor = vec4(color,1.0);
}
