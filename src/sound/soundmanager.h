#pragma once

#include <memory>
#include <string>
#include <unordered_map>
#include <list>

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>


namespace sf {
    class SoundBuffer;
}

class Sound;

class SoundManager {
public:
    SoundManager();
    void setListener(const glm::vec3& position, const glm::quat& orientation);
    std::shared_ptr<Sound> create(std::string soundFile);
    std::shared_ptr<Sound> play(std::string soundFile, const glm::vec3& position, bool relative);

protected:
    std::unordered_map<std::string, sf::SoundBuffer*> m_buffer;
    std::list<std::shared_ptr<Sound>> m_sounds;
    int m_nextCleanup;

    sf::SoundBuffer* obtain(std::string soundFile);
    void cleanUp();
};
