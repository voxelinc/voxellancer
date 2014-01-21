#pragma once

#include <memory>
#include <string>
#include <unordered_map>
#include <list>

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

namespace sf {
    class SoundBuffer;
    class Sound;
}

class SoundManager {
public:
    SoundManager();
    void setListener(glm::vec3 position, glm::quat orientation);
    std::weak_ptr<sf::Sound> play(std::string soundFile, glm::vec3 position, bool relative = false);

protected:
    std::unordered_map<std::string, sf::SoundBuffer*> m_buffer;
    std::vector<std::shared_ptr<sf::Sound>> m_sounds;
    int m_nextCleanup;

    sf::SoundBuffer* obtain(std::string soundFile);
    void cleanUp();
};