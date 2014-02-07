#version 330

uniform float withBorder;

flat in vec3 f_normal;
flat in float f_remainingLifetime;
in vec3 f_color;
in float f_emissiveness;
in vec3 modelposition;

const float border_size = 0.10;
const float border_darkness = 0.2;
const float ambient = 0.3;
const vec3 lightdir = normalize(vec3(0.3f, 0.5f, 1.0f));

layout(location=0) out vec4 fragColor;
layout(location=1) out vec4 normalz;
layout(location=2) out vec4 emissiveness;

void main() {
    if(f_remainingLifetime < 0) {
        discard;
    }

    // modelposition is between -0.5 and 0.5
    vec3 abspos = abs(modelposition);
    // get 2nd greatest component, sorting in glsl :D
    float border_dist = min(max(abspos.x, abspos.y), min(max(abspos.y, abspos.z), max(abspos.x, abspos.z))) * 2;
    float border = smoothstep(1-border_size, 1-border_size + 0.01, border_dist) * border_darkness ;

    vec3 n_normal = normalize(f_normal);
    float diffuse = dot(n_normal, lightdir);
    diffuse = max(0, diffuse) + ambient;

    fragColor = vec4(f_color * diffuse - vec3(border * withBorder), 1.0);
    emissiveness = vec4(f_color.xyz * f_emissiveness, 1.0);
    normalz = vec4((n_normal+1)/2, gl_FragCoord.z);
}
