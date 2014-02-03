#include "sound.h"

#include <SFML/Audio.hpp>


Sound::Sound(const sf::SoundBuffer& sound) :
    m_sound(new sf::Sound(sound))
{
}

Sound::~Sound() = default;

Sound::Status Sound::status() {
    switch (m_sound->getStatus()) {
        case sf::SoundSource::Playing:
            return Playing;
        case sf::SoundSource::Paused:
            return Paused;
        case sf::SoundSource::Stopped:
            return Stopped;
        default:
            return Stopped;
    }
}

void Sound::play() {
  //  m_sound->play();
}

void Sound::stop() {
    m_sound->stop();
}

void Sound::pause() {
    m_sound->pause();
}

Sound* Sound::setPosition(const glm::vec3& p) {
    m_sound->setPosition(sf::Vector3f(p.x, p.y, p.z));
    return this;
}

Sound* Sound::setAttenuation(float attenuation) {
    m_sound->setAttenuation(attenuation);
    return this;
}

Sound* Sound::setVolume(float volume) {
    m_sound->setVolume(volume);
    return this;
}

Sound* Sound::setLooping(bool loop) {
    m_sound->setLoop(loop);
    return this;
}

Sound* Sound::setRelativeToListener(bool relative) {
    m_sound->setRelativeToListener(relative);
    return this;
}

Sound* Sound::setMinDistance(float distance) {
    m_sound->setMinDistance(distance);
    return this;
}

