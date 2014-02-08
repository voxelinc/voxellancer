#version 330

uniform float withBorder;

flat in vec3 f_normal;
flat in float f_remainingLifetime;
in vec3 f_color;
in float f_emissiveness;
in vec3 modelposition;

layout(location = 0) out vec4 fragColor;
layout(location = 1) out vec4 normalz;
layout(location = 2) out vec4 emissiveness;

vec4 voxelFragmentColor(vec3 color, float emissiveness, vec3 normal, vec3 positionInVoxel);
vec4 voxelFragmentEmissiveness(vec3 color, float emissiveness);
vec4 voxelFragmenNormalZ(vec3 normal);

void main() {
    if(f_remainingLifetime < 0) {
        discard;
    }

    fragColor = voxelFragmentColor(f_color, f_emissiveness, f_normal, modelposition);
	emissiveness = voxelFragmentEmissiveness(f_color, f_emissiveness);
	normalz = voxelFragmenNormalZ(f_normal);
}

