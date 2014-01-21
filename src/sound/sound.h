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
    enum Status {
        Paused, Playing, Stopped
    };

    Sound(const sf::SoundBuffer& sound);

    Status status();

    void play();
    void stop();
    void pause();

    Sound* setPosition(const glm::vec3& position);
    Sound* setVolume(float volume);
    Sound* setAttenuation(float attenuation);
    Sound* setLoop(bool loop);
    Sound* setRelativeToListener(bool relative);
private:
    std::unique_ptr<sf::Sound> m_sound;
};

