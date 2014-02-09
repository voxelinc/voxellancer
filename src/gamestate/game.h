#pragma once

#include "etc/hmd/hmdmanager.h"

#include "gamestate.h"


class InGame;

/*
    Mainstate of the Game, entered once when libraries and context are setup
    and left just before they are teared down again
*/
class Game: public GameState {
public:
    Game();

    HMDManager& hmdManager();
    Viewer& viewer();

    virtual void update(float deltaSec) override;


protected:
    HMDManager m_hmdManager;
    Viewer m_viewer;

    InGame* m_inGame;
};

