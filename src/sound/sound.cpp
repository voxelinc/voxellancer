#include "sound.h"

#include <SFML/Audio.hpp>


Sound::Sound(const sf::SoundBuffer& sound) :
    m_sound(new sf::Sound(sound))
{
}

Sound::Sound():
    m_sound(nullptr)
{
}

Sound::~Sound() = default;

Sound::Status Sound::status() {
    if (!m_sound) {
        return Status::Null;
    }
    switch (m_sound->getStatus()) {
        case sf::SoundSource::Playing:
            return Status::Playing;
        case sf::SoundSource::Paused:
            return Status::Paused;
        case sf::SoundSource::Stopped:
            return Status::Stopped;
        default:
            return Status::Stopped;
    }
}

void Sound::play() {
    if (m_sound) {
        m_sound->play();
    }
}

void Sound::stop() {
    if (m_sound) {
        m_sound->stop();
    }
}

void Sound::pause() {
    if (m_sound) {
        m_sound->pause();
    }
}

Sound& Sound::setPosition(const glm::vec3& p) {
    if (m_sound) {
        m_sound->setPosition(sf::Vector3f(p.x, p.y, p.z));
    }
    return *this;
}

Sound& Sound::setAttenuation(float attenuation) {
    if (m_sound) {
        m_sound->setAttenuation(attenuation);
    }
    return *this;
}

Sound& Sound::setVolume(float volume) {
    if (m_sound) {
        m_sound->setVolume(volume * 100);
    }
    return *this;
}

Sound& Sound::setLooping(bool loop) {
    if (m_sound) {
        m_sound->setLoop(loop);
    }
    return *this;
}

Sound& Sound::setRelativeToListener(bool relative) {
    if (m_sound) {
        m_sound->setRelativeToListener(relative);
    }
    return *this;
}

Sound& Sound::setMinDistance(float distance) {
    if (m_sound) {
        m_sound->setMinDistance(distance);
    }
    return *this;
}

