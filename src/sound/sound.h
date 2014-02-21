#pragma once

#include <memory>
#include <glm/glm.hpp>


namespace sf {
    class Sound;
    class SoundBuffer;
}

class Sound {
public:
    enum class Status {
        Paused, Playing, Stopped, Disabled
    };

    Sound();
    Sound(const sf::SoundBuffer& sound);
    ~Sound();

    Status status();

    void play();
    void stop();
    void pause();

    Sound* setPosition(const glm::vec3& position);
    Sound* setVolume(float volume);
    Sound* setAttenuation(float attenuation);
    Sound* setLooping(bool loop);
    Sound* setRelativeToListener(bool relative);
    Sound* setMinDistance(float distance);

protected:
    std::unique_ptr<sf::Sound> m_sound;
};

