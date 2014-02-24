#include "soundproperties.h"

#include "property/property.h"


SoundProperties::SoundProperties(const std::string& sound, float volume, float attenuation, bool repeating):
    m_sound(sound),
    m_volume(volume),
    m_attenuation(attenuation),
    m_looping(repeating)
{

}

const std::string& SoundProperties::sound() const {
    return m_sound;
}

const float SoundProperties::volume() const {
    return m_volume;
}

const float SoundProperties::attenuation() const {
    return m_attenuation;
}

const bool SoundProperties::looping() const {
    return m_looping;
}

SoundProperties SoundProperties::fromProperties(const std::string& prefix) {
    return SoundProperties(
            Property<std::string>::get(prefix + ".name"),
            Property<float>::get(prefix + ".volume", 1.0f),
            Property<float>::get(prefix + ".attenuation", 1.0f),
            Property<bool>::get(prefix + ".looping", false)
        );
}

