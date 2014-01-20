#include "SoundManager.h"

#include <glow/logging.h>

#include <SFML/Audio.hpp>

SoundManager::SoundManager() :
    m_buffer(),
    m_sounds()
{
    setListener(glm::vec3(0), glm::quat());
}

void SoundManager::setListener(glm::vec3 p, glm::quat orientation) {
    glm::vec3 d = orientation * glm::vec3(0, 0, -1);
    sf::Listener::setPosition(sf::Vector3f(p.x, p.y, p.z));
    sf::Listener::setDirection(sf::Vector3f(d.x, d.y, d.z));
}

std::weak_ptr<sf::Sound> SoundManager::play(std::string soundFile, glm::vec3 p, bool relative) {
    std::shared_ptr<sf::Sound> sound = std::make_shared<sf::Sound>(*obtain(soundFile));
    assert(sound->getBuffer()->getChannelCount() == 1); // sounds with more than one channel don't work with positions!
    sound->setPosition(sf::Vector3f(p.x, p.y, p.z));
    //sound->setRelativeToListener(relative);
    sound->setAttenuation(0.05f);
    sound->play();
    sound->setLoop(true);
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

