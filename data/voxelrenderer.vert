#version 120
#extension GL_ARB_draw_instanced : require

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform mat4 viewProjection;

uniform sampler1D positionSampler;
uniform sampler1D colorSampler;


void main()
{
    vec3 offset = texelFetch(positionSampler, gl_InstanceIDARB, 0).xyz * 255;
    
    gl_Color = texelFetch(colorSampler, gl_InstanceIDARB, 0).xyz;        
	gl_Position = viewProjection * model * (vec4(a_vertex + offset, 1.0));
}
