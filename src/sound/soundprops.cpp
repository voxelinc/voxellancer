#include "soundprops.h"

#include "property/property.h"


SoundProps::SoundProps(const std::string& sound, float volume, float attenuation, bool repeating):
    m_sound(sound),
    m_volume(volume),
    m_attenuation(attenuation),
    m_looping(repeating)
{

}

const std::string& SoundProps::sound() const {
    return m_sound;
}

const float SoundProps::volume() const {
    return m_volume;
}

const float SoundProps::attenuation() const {
    return m_attenuation;
}

const bool SoundProps::looping() const {
    return m_looping;
}

SoundProps SoundProps::fromProperties(std::string prefix) {
    return SoundProps(
            Property<std::string>::get(prefix + ".name"),
            Property<float>::get(prefix + ".volume", 1.0f),
            Property<float>::get(prefix + ".attenuation", 1.0f),
            Property<bool>::get(prefix + ".looping", false)
        );
}

