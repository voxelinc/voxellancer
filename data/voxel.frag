#version 130

flat in vec3 f_normal;
flat in vec3 f_color;
in vec3 modelposition;

out vec4 fragColor;

void main() {
    float border_size = 0.05;
    float border_darkness = 0.2;

    // modelposition is between -0.5 and 0.5
    vec3 abspos = abs(modelposition);
    // get 2nd greatest component, sorting in glsl :D
    float border_dist = min(max(abspos.x, abspos.y), min(max(abspos.y, abspos.z), max(abspos.x, abspos.z))) * 2;
    float border = smoothstep(1-border_size, 1-border_size + 0.01, border_dist) * border_darkness ;

    vec3 lightdir = normalize(vec3(0.3f, 0.5f, 1.0f));
    vec3 n_normal = normalize(f_normal);
    float diffuse = dot(n_normal, lightdir);
    diffuse = max(0, diffuse) + 0.2;
    
    fragColor = vec4(f_color * diffuse - border, 1.0);
}
