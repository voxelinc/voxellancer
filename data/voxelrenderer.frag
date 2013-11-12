#version 400


uniform sampler1D positionSampler;

in vec2 v_uv;
flat in vec3 normal;
in vec3 color;

layout (location = 0) out vec4 fragColor;

void main()
{
    vec3 lightdir = normalize(vec3(0.1f, 0.2f, 1.0f));
    vec3 n_normal = normalize(normal);
    float diffuse = dot(n_normal, lightdir);
    diffuse = max(0, diffuse) + 0.1;
    
    fragColor = vec4(color * diffuse, 1.0);

    //fragColor = vec4(n_normal + 1.0f / 2.0f, 1.0f);
}
