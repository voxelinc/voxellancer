#pragma once

#include <string>

class SoundProperties {
public:
    SoundProperties() = default;
    SoundProperties(const std::string& sound, float volume, float attenuation, bool repeating);

    const std::string& sound() const;
    const float volume() const;
    const float attenuation() const;
    const bool looping() const;

    static SoundProperties fromProperties(std::string prefix);

protected:
    std::string m_sound;
    float m_volume;
    float m_attenuation;
    bool m_looping;

};