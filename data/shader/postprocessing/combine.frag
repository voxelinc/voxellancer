#version 330

uniform ivec2 viewport;

uniform sampler2D color;
uniform sampler2D bloom;
uniform sampler2D transparencyAcc;
uniform sampler2D transparencyCnt;

in vec2 v_uv;

layout(location = 0) out vec4 fragColor;


// Implements Weighted Average
// see http://www.slideshare.net/acbess/order-independent-transparency-presentation slide 27
// and http://jcgt.org/published/0002/02/09/paper.pdf p 127
void main() {
    vec4 opaque = texture(color, v_uv);
    vec4 accumulated = texture(transparencyAcc, v_uv);

    // HACK: actually accumulated.a should be the accumulation of the a values
    // It seems to always be 1, while using the count-buffer's z for the same purpose works
    accumulated.a = texture(transparencyCnt, v_uv).z;

    uint nTransparentLayers = uint(texture(transparencyCnt, v_uv).x * 255);

    vec4 weightedAverage = vec4(0.0);
    // build the weighted average of the transparent colors, where the alpha value is the weight
    if (nTransparentLayers > uint(0)) {
        weightedAverage = vec4(accumulated.rgb / accumulated.a, accumulated.a / nTransparentLayers);
    }

    // blend the transparent average over the opaque surface
    // the more transparent fragments there were, the fewer of the background is taken into account
	// finally add the bloom on top. Note the bloom of obscured opaque surfaces will "shine through" entirely
    weightedAverage.a = pow(1.0 - weightedAverage.a, nTransparentLayers);

    fragColor = weightedAverage * (1.0 - weightedAverage.a) +
                opaque * weightedAverage.a +
                texture(bloom, v_uv);
}

