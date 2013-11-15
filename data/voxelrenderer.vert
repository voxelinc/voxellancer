#version 130
#extension GL_ARB_draw_instanced : require

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform mat4 viewProjection;

uniform sampler1D positionSampler;
uniform sampler1D colorSampler;

in vec3 a_vertex;
in vec3 a_normal;

flat out vec3 normal;
out vec3 color;
out vec3 modelposition;

void main()
{
	modelposition = a_vertex;

    // map [0:1] to [-128:127]
    vec3 offset = texelFetch(positionSampler, gl_InstanceIDARB, 0).xyz * 255 - 128;
    
    color = texelFetch(colorSampler, gl_InstanceIDARB, 0).xyz;
        
	gl_Position = viewProjection * model * (vec4(a_vertex + offset, 1.0));
    
    normal = (model * vec4(a_normal, 0.0)).xyz;
}
