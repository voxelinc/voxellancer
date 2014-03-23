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
class SoundProperties;

class SoundManager {
public:
    SoundManager();
    ~SoundManager();

    void setListener(const glm::vec3& position, const glm::quat& orientation);
    std::shared_ptr<Sound> create(std::string soundFile);
    std::shared_ptr<Sound> play(std::string soundFile, const glm::vec3& position, bool relative = false);
    std::shared_ptr<Sound> play(const SoundProperties& soundProperties, const glm::vec3& position, bool relative = false);

    void activate();
    void deactivate();


    void stopAll();

    static SoundManager* current();


protected:
    std::unordered_map<std::string, sf::SoundBuffer*> m_buffer;
    std::list<std::shared_ptr<Sound>> m_sounds;
    int m_nextCleanup;

    sf::SoundBuffer* obtain(std::string soundFile);
    void cleanUp();
    void forcedCleanup();
    std::shared_ptr<Sound> createNullSound();

    static SoundManager* s_current;
};

