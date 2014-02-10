#version 330
#extension GL_ARB_separate_shader_objects : enable

uniform float withBorder;

layout(location = 0) out vec4 fragColor;
layout(location = 1) out vec4 normalz;
layout(location = 2) out vec4 emissiveness;

layout(location = 0) flat in vec3 f_normal;
layout(location = 1) in vec3 f_color;
layout(location = 2) in float f_emissiveness;
layout(location = 3) in vec3 f_modelposition;

const float borderWidth = 0.10;
const float borderDarkness = 0.2;
const float ambient = 0.3;
const vec3 lightDirection = normalize(vec3(0.3f, 0.5f, 1.0f));

vec4 voxelFragmentColor(vec3 color, float emissiveness, vec3 normal, vec3 positionInVoxel) {
    // modelposition is between -0.5 and 0.5
    vec3 absPositionInModel = abs(positionInVoxel);

    // get 2nd greatest component, sorting in glsl :D
    float borderDistance = min(max(absPositionInModel.x, absPositionInModel.y),
                               min(max(absPositionInModel.y, absPositionInModel.z),
                                   max(absPositionInModel.x, absPositionInModel.z))) * 2;

    float border = smoothstep(1.0 - borderWidth, 1.0 - borderWidth + 0.01, borderDistance) * borderDarkness;

    vec3 n_normal = normalize(normal);
    float diffuse = dot(n_normal, lightDirection);
    diffuse = max(0, diffuse) + ambient;

    return vec4(color * diffuse - vec3(border * float(withBorder)), 1.0);
}

vec4 voxelFragmentEmissiveness(vec3 color, float emissiveness) {
    return vec4(color.xyz * emissiveness, 1.0);
}

vec4 voxelFragmenNormalZ(vec3 normal) {
    vec3 n_normal = normalize(normal);
    return vec4((n_normal + 1.0) / 2.0, gl_FragCoord.z);
}

void main() {
    fragColor = voxelFragmentColor(f_color, f_emissiveness, f_normal, f_modelposition);
    emissiveness = voxelFragmentEmissiveness(f_color, f_emissiveness);
    normalz = voxelFragmenNormalZ(f_normal);
}

