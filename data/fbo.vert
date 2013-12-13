#version 330 core

// Input vertex data, different for all executions of this shader.
layout(location = 0) in vec3 vertex;

// Output data ; will be interpolated for each fragment.
out vec2 UV;

void main(){
	gl_Position =  vec4(vertex,1);
	UV = (vertex.xy+vec2(1,1))/2.0;
}

