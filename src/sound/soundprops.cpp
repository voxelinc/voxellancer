#include "SoundProps.h"

#include "property/property.h"


SoundProps::SoundProps(const std::string& sound, float volume):
    m_sound(sound),
    m_volume(volume)
{

}

const std::string& SoundProps::sound() const {
    return m_sound;
}

const float SoundProps::volume() const {
    return m_volume;
}


SoundProps SoundProps::fromProperties(std::string prefix) {
    return SoundProps(
            Property<std::string>::get(prefix + ".name"),
            Property<float>::get(prefix + ".volume", 100.0f)
        );
}


