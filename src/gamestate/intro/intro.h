#pragma once

#include <list>
#include <string>

#include "gamestate/gamestate.h"


class CameraHead;
class CameraDolly;
class Game;
class IntroScene;
class IntroInput;
class Trigger;

class Intro : public GameState {
public:
    Intro(Game* game);
    ~Intro() override;

    /**
     * GameState overrides
     */

    const Scene& scene() const override;
    const CameraHead& cameraHead() const override;

    InputHandler& inputHandler() override;

    void update(float deltaSec) override;

    void onEntered() override;
    void onLeft() override;


    /**
     * Intro-specifics
     */

    Trigger& overTrigger();

    std::list<std::string> lines() const;


protected:
    std::unique_ptr<IntroScene> m_scene;
    std::unique_ptr<CameraDolly> m_cameraDolly;
    std::unique_ptr<CameraHead> m_cameraHead;
    std::unique_ptr<IntroInput> m_input;

    std::unique_ptr<Trigger> m_overTrigger;
    std::list<std::string> m_lines;
    int m_currentLine;
    int m_currentLetter;
    float m_letterCountdown;
    float m_showCountdown;
};


