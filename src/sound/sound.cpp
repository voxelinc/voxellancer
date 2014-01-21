#include "sound.h"

#include <SFML/audio.hpp>

Sound::Sound(const sf::SoundBuffer& sound) :
    m_sound(std::make_shared<sf::Sound>(sound))
{

}

void Sound::setPosition(const glm::vec3& p) {
    m_sound->setPosition(sf::Vector3f(p.x, p.y, p.z));
}

void Sound::play() {
    m_sound->play();
}

void Sound::setAttenuation(float attenuation) {
    m_sound->setAttenuation(attenuation);
}

void Sound::setLoop(bool loop) {
    m_sound->setLoop(loop);
}

void Sound::setRelativeToListener(bool relative) {
    m_sound->setRelativeToListener(relative);
}
