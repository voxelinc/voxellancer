#pragma once

#include "etc/hmd/hmdmanager.h"

#include "gamestate.h"


class GamePlay;

/*
    Mainstate of the Game, entered once when libraries and context are setup
    and left just before they are teared down again
*/
class Game: public GameState {
public:
    Game();

    virtual const Scene& scene() const override;
    virtual const CameraHead& cameraHead() const override;

    HMDManager& hmdManager();
    Viewer& viewer();

    virtual void update(float deltaSec) override;

    void draw();


protected:
    HMDManager m_hmdManager;
    Viewer m_viewer;

    GamePlay* m_gamePlay;
};

