#pragma once

#include <memory>

#include "gamestate.h"


class GamePlay;
class HMDManager;
class Viewer;

/*
    Mainstate of the Game, entered once when libraries and context are setup
    and left just before they are teared down again
*/
class Game: public GameState {
public:
    Game();
    ~Game();

    GamePlay& gamePlay();

    virtual const Scene& scene() const override;
    virtual const CameraHead& cameraHead() const override;

    HMDManager& hmdManager();
    Viewer& viewer();

    virtual void update(float deltaSec) override;

    void draw();


protected:
    std::shared_ptr<HMDManager> m_hmdManager;
    std::unique_ptr<Viewer> m_viewer;

    GamePlay* m_gamePlay;
};

