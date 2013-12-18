#version 130

uniform sampler1D positionSampler;
uniform float withBorder;

flat in vec3 normal;
in vec3 color;
in vec3 modelposition;

//layout (location = 0) 
out vec4 fragColor;

void main()
{
    float border_size = 0.05;
    float border_darkness = 0.2;

    // modelposition is between -0.5 and 0.5
    vec3 abspos = abs(modelposition);
    // get 2nd greatest component, sorting in glsl :D
    float border_dist = min(max(abspos.x, abspos.y), min(max(abspos.y, abspos.z), max(abspos.x, abspos.z))) * 2;
    float border = smoothstep(1-border_size, 1-border_size + 0.01, border_dist) * border_darkness ;

    vec3 lightdir = normalize(vec3(0.3f, 0.5f, 1.0f));
    vec3 n_normal = normalize(normal);
    float diffuse = dot(n_normal, lightdir);
    diffuse = max(0, diffuse) + 0.2;
    
    //fragColor = vec4(vec3(border), 1.0);
    fragColor = vec4(color * diffuse - border * withBorder, 1.0);

    //fragColor = vec4(n_normal + 1.0f / 2.0f, 1.0f);
}
