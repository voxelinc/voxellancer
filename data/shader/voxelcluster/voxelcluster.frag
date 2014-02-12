#version 330

uniform float withBorder;

layout(location = 0) out vec4 fragColor;
layout(location = 1) out vec4 normalz;
layout(location = 2) out vec4 emissiveness;

layout(location = 0) flat in vec3 f_normal;
layout(location = 1) in vec3 f_color;
layout(location = 2) in float f_emissiveness;
layout(location = 3) in vec3 f_modelposition;


vec4 voxelFragmentColor(vec3 color, float emissiveness, vec3 normal, vec3 positionInVoxel);
vec4 voxelFragmentEmissiveness(vec3 color, float emissiveness);
vec4 voxelFragmenNormalZ(vec3 normal);


void main() {
    fragColor = voxelFragmentColor(f_color, f_emissiveness, f_normal, f_modelposition);
    emissiveness = voxelFragmentEmissiveness(f_color, f_emissiveness);
    normalz = voxelFragmenNormalZ(f_normal);
}

