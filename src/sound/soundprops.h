#pragma once

#include <string>

class SoundProps {
public:
    SoundProps() = default;
    SoundProps(const std::string& sound, float volume, float attenuation, bool repeating);

    const std::string& sound() const;
    const float volume() const;
    const float attenuation() const;
    const bool looping() const;

    static SoundProps fromProperties(std::string prefix);

protected:
    std::string m_sound;
    float m_volume;
    float m_attenuation;
    bool m_looping;

};