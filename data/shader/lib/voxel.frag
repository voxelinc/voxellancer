#version 330

uniform float withBorder;
uniform vec3 lightdir;

const float borderWidth = 0.10;
const float borderDarkness = 0.2;
const float ambient = 0.3;

vec3 voxelFragmentColor(vec3 color, float emissiveness, vec3 normal, vec3 positionInVoxel) {
    // modelposition is between -0.5 and 0.5
    vec3 absPositionInModel = abs(positionInVoxel);

    // get 2nd greatest component, sorting in glsl :D
    float borderDistance = min(max(absPositionInModel.x, absPositionInModel.y),
                               min(max(absPositionInModel.y, absPositionInModel.z),
                                   max(absPositionInModel.x, absPositionInModel.z))) * 2;

    float border = smoothstep(1.0 - borderWidth, 1.0 - borderWidth + 0.01, borderDistance) * borderDarkness;

    vec3 n_normal = normalize(normal);
    float diffuse = dot(n_normal, lightdir);
    diffuse = max(0, diffuse) + ambient;

    return color * diffuse - vec3(border * float(withBorder));
}

vec4 voxelFragmentEmissiveness(vec3 color, float emissiveness) {
    return vec4(color.xyz * emissiveness, 1.0);
}

vec4 voxelFragmenNormalZ(vec3 normal) {
    vec3 n_normal = normalize(normal);
    return vec4((n_normal + 1.0) / 2.0, gl_FragCoord.z);
}


