#version 130

uniform sampler2D texture;
uniform vec2 offset;
uniform vec2 scale;
uniform vec4 distortionKs;

in vec2 f_texCoord;

out vec3 fragColor;

vec2 HmdWarp(vec2 linear) {
    float radiusSquared = linear.x * linear.x + linear.y * linear.y;
    vec2 rvector = linear * (
        distortionKs.x +
        distortionKs.y * radiusSquared +
        distortionKs.z * radiusSquared * radiusSquared +
        distortionKs.w * radiusSquared * radiusSquared * radiusSquared
    );
    return rvector;
}

void main() {
    vec2 eyeC = (f_texCoord-0.5) * 2.0;
    vec2 texC = HmdWarp(eyeC);

    if(texC.x < 0 || texC.x > 1) {
        discard;
    }
    if(texC.y < 0 || texC.y > 1) {
        discard;
    }

    fragColor = texture2D(texture, eyeC);
}

