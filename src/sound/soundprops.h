#pragma once

#include <string>

class SoundProps {
public:
    SoundProps() = default;
    SoundProps(const std::string& sound, float volume);

    const std::string& sound() const;
    const float volume() const;

    static SoundProps fromProperties(std::string prefix);

protected:
    std::string m_sound;
    float m_volume;

};