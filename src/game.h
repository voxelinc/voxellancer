#pragma once

#include <memory>

#include "etc/hmd/hmdmanager.h"

#include "display/viewer.h"
#include "display/gamescene.h"

#include "ui/inputhandler.h"

#include "scenarios/gamescenario.h"
#include "scenarios/battlescenario.h"

#include "player.h"


class SoundManager;

class Game {
public:
    Game();

    InputHandler& inputHandler();
    Player& player();
    Viewer& viewer();
    HMDManager& hmdManager();

    void update(float deltaSec);
    void draw();

    void setOutputBuffer(int i);


private:
    Player m_player;
    InputHandler m_inputHandler;
    Viewer m_viewer;
    GameScene m_gameScene;
    BattleScenario m_scenario;
    HMDManager m_hmdManager;
};

