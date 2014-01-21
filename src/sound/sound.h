#pragma once

#include <memory>
#include <glm/glm.hpp>

namespace sf {
    class Sound;
    class SoundBuffer;
}


class Sound
{
public:
    Sound(const sf::SoundBuffer& sound);

    void setPosition(const glm::vec3& position);
    void play();
    void setAttenuation(float attenuation);
    void setLoop(bool loop);
    void setRelativeToListener(bool relative);
private:
    std::shared_ptr<sf::Sound> m_sound;
};

