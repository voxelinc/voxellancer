#include "soundmanager.h"

#include <SFML/Audio.hpp>

#include <glow/logging.h>

#include "sound.h"
#include "soundproperties.h"


SoundManager* SoundManager::s_current;
static const int CLEANUP_PERIOD = 100;

SoundManager::SoundManager() :
    m_buffer(),
    m_sounds(),
    m_nextCleanup(0)
{
    setListener(glm::vec3(0), glm::quat());
}

SoundManager::~SoundManager() {
    if (s_current == this) {
        s_current = nullptr;
    }
}

void SoundManager::setListener(const glm::vec3& p, const glm::quat& orientation) {
    glm::vec3 d = orientation * glm::vec3(0, 0, -1);
    sf::Listener::setPosition(sf::Vector3f(p.x, p.y, p.z));
    sf::Listener::setDirection(sf::Vector3f(d.x, d.y, d.z));
}

std::shared_ptr<Sound> SoundManager::play(std::string soundFile, const glm::vec3& position, bool relative) {
    if (soundFile == "null") {
        return std::make_shared<Sound>();
    }
    std::shared_ptr<Sound> sound = create(soundFile);
    sound->setPosition(position).setRelativeToListener(relative).play();
    return sound;
}

std::shared_ptr<Sound> SoundManager::play(const SoundProperties& soundProperties, const glm::vec3& position, bool relative) {
    std::shared_ptr<Sound> sound = play(soundProperties.sound(), position, relative);
    sound->setVolume(soundProperties.volume());
    sound->setLooping(soundProperties.looping());
    sound->setAttenuation(soundProperties.attenuation());
    return sound;
}

std::shared_ptr<Sound> SoundManager::create(std::string soundFile) {
    cleanUp();

    sf::SoundBuffer* buffer = obtain(soundFile);
    // sounds don't work with more than one channel!
    assert(buffer->getChannelCount() == 1);

    std::shared_ptr<Sound> sound(std::make_shared<Sound>(*buffer));
    sound->setAttenuation(0.1f);
    sound->setMinDistance(5.0f);
    m_sounds.push_back(sound);

    return sound;
}

sf::SoundBuffer* SoundManager::obtain(std::string soundFile) {
    sf::SoundBuffer* buffer = m_buffer[soundFile];
    if (buffer == nullptr) {
        buffer = new sf::SoundBuffer();
        if (!buffer->loadFromFile(soundFile)) {
            glow::warning("SoundManager: could not load %;", soundFile);
        }
        m_buffer[soundFile] = buffer;
    }
    return buffer;
}

void SoundManager::cleanUp() {
    if (m_nextCleanup++ < CLEANUP_PERIOD) {
        return;
    }
    for (std::list<std::shared_ptr<Sound>>::iterator iter = m_sounds.begin(); iter != m_sounds.end();)
    {
        if ((*iter)->status() == Sound::Status::Stopped) {
            iter = m_sounds.erase(iter);
        } else {
            ++iter;
        }
    }
    m_nextCleanup = 0;
}

void SoundManager::forcedCleanup() {
    m_nextCleanup = CLEANUP_PERIOD;
    cleanUp();
}

SoundManager* SoundManager::current() {
    assert(s_current != nullptr);
    return s_current;
}

void SoundManager::activate() {
    if (s_current == this) {
        return;
    }
    assert(s_current == nullptr);

    s_current = this;

    for (std::shared_ptr<Sound>& sound : m_sounds) {
        if (sound->status() == Sound::Status::Paused) {
            sound->play();
        }
    }
}

void SoundManager::deactivate() {
    assert(s_current == this);
    s_current = nullptr;

    forcedCleanup();


    for (std::shared_ptr<Sound>& sound : m_sounds) {
        if (sound->status() == Sound::Status::Playing) {
            sound->pause();
        }
    }
}

void SoundManager::stopAll() {
    for (std::shared_ptr<Sound>& sound : m_sounds) {
        if (sound->status() != Sound::Status::Stopped) {
            sound->stop();
        }
    }
    forcedCleanup();
}


