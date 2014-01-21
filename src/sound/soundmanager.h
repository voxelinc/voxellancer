#pragma once

#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

#include "sound.h"

namespace sf {
    class SoundBuffer;
}

class SoundManager {
public:
    SoundManager();
    void setListener(glm::vec3 position, glm::quat orientation);
    Sound play(std::string soundFile, glm::vec3 position, bool relative = false);

protected:
    std::unordered_map<std::string, sf::SoundBuffer*> m_buffer;
    std::vector<Sound> m_sounds;

    sf::SoundBuffer* obtain(std::string soundFile);
};