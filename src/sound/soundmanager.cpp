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

static const int CLEANUPPERIOD = 100;

std::shared_ptr<Sound> SoundManager::play(std::string soundFile, glm::vec3 position) {
    std::shared_ptr<Sound> sound = create(soundFile);
    sound->setPosition(position)->play();
    return sound;
}

std::shared_ptr<Sound> SoundManager::create(std::string soundFile) {
    cleanUp();

    sf::SoundBuffer* buffer = obtain(soundFile);
    // sounds don't work with more than one channel!
    assert(buffer->getChannelCount() == 1);

    std::shared_ptr<Sound> sound(new Sound(*buffer));
    sound->setAttenuation(0.05f);
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

void SoundManager::cleanUp()
{
    if (m_nextCleanup++ < CLEANUPPERIOD) {
        return;
    }
    for (std::list<std::shared_ptr<Sound>>::iterator iter = m_sounds.begin(); iter != m_sounds.end();)
    {
        if ((*iter)->status() == Sound::Stopped) {
            iter = m_sounds.erase(iter);
        } else {
            ++iter;
        }
    }
    m_nextCleanup = 0;

}
