#version 330

uniform float withBorder;

layout(location = 0) out vec4 fragColor;
layout(location = 1) out vec4 normalz;
layout(location = 2) out vec4 emissiveness;
layout(location = 3) out vec4 count;

flat in vec3 f_normal;
in vec4 f_color;
in float f_emissiveness;
in vec3 f_modelposition;


vec3 voxelFragmentColor(vec3 color, float emissiveness, vec3 normal, vec3 positionInVoxel);
vec4 voxelFragmentEmissiveness(vec3 color, float emissiveness);
vec4 voxelFragmenNormalZ(vec3 normal);


void main() {
	vec3 rgbColor = voxelFragmentColor(f_color.rgb, f_emissiveness, f_normal, f_modelposition);
    fragColor = vec4(rgbColor * f_color.a, f_color.a);
    emissiveness = voxelFragmentEmissiveness(f_color.rgb, f_emissiveness);
    normalz = voxelFragmenNormalZ(f_normal);
	count = vec4(f_color.a, f_color.a, f_color.a, 1.0);
}

