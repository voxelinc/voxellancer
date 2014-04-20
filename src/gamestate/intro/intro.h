#pragma once

#include "gamestate/gamestate.h"


class CameraHead;
class CameraDolly;
class Game;
class IntroScene;

class Intro : public GameState {
public:
    Intro(Game* game);

    virtual const Scene& scene() const;
    virtual const CameraHead& cameraHead() const;

    virtual void update(float deltaSec) override;

    virtual void onEntered() override;
    virtual void onLeft() override;


protected:
    std::unique_ptr<IntroScene> m_scene;
    std::unique_ptr<CameraDolly> m_cameraDolly;
    std::unique_ptr<CameraHead> m_cameraHead;
};


