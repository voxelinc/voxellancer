#version 330

uniform float time;
uniform float withBorder;

layout(location = 0) out vec4 fragColor;
layout(location = 1) out vec4 normalz;
layout(location = 2) out vec4 emissiveness;

in vec3 f_color;
flat in vec3 f_normal;
in float f_deathTime;
in float f_emissiveness;
in vec3 f_modelposition;


vec3 voxelFragmentColor(vec3 color, float emissiveness, vec3 normal, vec3 positionInVoxel);
vec4 voxelFragmentEmissiveness(vec3 color, float emissiveness);
vec4 voxelFragmenNormalZ(vec3 normal);


void main() {
    if (time >= f_deathTime) {
        discard;
    }

    fragColor = vec4(voxelFragmentColor(f_color, f_emissiveness, f_normal, f_modelposition), 1.0);
    emissiveness = voxelFragmentEmissiveness(f_color, f_emissiveness);
    normalz = voxelFragmenNormalZ(f_normal);
}

