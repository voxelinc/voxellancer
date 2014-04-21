#version 330

uniform ivec2 viewport;

uniform sampler2D color;
uniform sampler2D bloom;
uniform sampler2D transparencyAcc;
uniform sampler2D transparencyCnt;

in vec2 v_uv;

layout(location=0) out vec4 fragColor;

void main() {	
	vec4 opaque = texture(color, v_uv) + texture(bloom, v_uv);
	vec4 accumulated = texture(transparencyAcc, v_uv);
	accumulated.a = texture(transparencyCnt, v_uv).z; // Why is Acc.a always 1?!
	uint currentN = uint(texture(transparencyCnt, v_uv).x * 255);

	vec4 weightedAverage = vec4(0.0);
	if (currentN > uint(0)) {
		weightedAverage = vec4(accumulated.rgb / accumulated.a, accumulated.a / currentN);
	}
	weightedAverage.a = pow(1 - weightedAverage.a, currentN);

	fragColor = weightedAverage * (1 - weightedAverage.a) + opaque * weightedAverage.a;

}