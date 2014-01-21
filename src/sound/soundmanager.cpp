#include "soundmanager.h"

#include <glow/logging.h>

#include <SFML/Audio.hpp>

SoundManager::SoundManager() :
    m_buffer(),
    m_sounds(),
    m_nextCleanup(0)
{
    setListener(glm::vec3(0), glm::quat());
}

void SoundManager::setListener(glm::vec3 p, glm::quat orientation) {
    glm::vec3 d = orientation * glm::vec3(0, 0, -1);
    sf::Listener::setPosition(sf::Vector3f(p.x, p.y, p.z));
    sf::Listener::setDirection(sf::Vector3f(d.x, d.y, d.z));
}

Sound SoundManager::play(std::string soundFile, glm::vec3 position, bool relative) {
    sf::SoundBuffer* buffer = obtain(soundFile);
    // sounds don't work with more than one channel!
    assert(buffer->getChannelCount() == 1);

    Sound sound(*buffer);
    sound.setPosition(position);
    //sound->setRelativeToListener(relative);
    sound.setAttenuation(0.05f);
    sound.play();
    sound.setLoop(true);
    m_sounds.push_back(sound);

    m_nextCleanup++;
    if (m_nextCleanup == 100) {
        cleanUp();
    }
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

void SoundManager::cleanUp()
{
    for (auto iter = m_sounds.begin(); iter != m_sounds.end();)
    {
        sf::Sound * sound = iter->get();
        if (sound->getStatus() == sf::SoundSource::Stopped) {
            iter = m_sounds.erase(iter);
        } else {
            ++iter;
        }
    }
}

