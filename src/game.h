#pragma once

#include <memory>

#include "etc/hmd/hmdmanager.h"

#include "display/viewer.h"
#include "display/gamescene.h"

#include "ui/inputhandler.h"

#include "player.h"

class SoundManager;

class Game {
public:
    Game();

    InputHandler& inputHandler();
    Player& player();
    Viewer& viewer();
    HMDManager& hmdManager();
    SoundManager& soundManager();

    void initialize();

    void update(float deltaSec);
    void draw();


private:
    InputHandler m_inputHandler;
    Player m_player;
    Viewer m_viewer;
    GameScene m_gameScene;
    HMDManager m_hmdManager;
    std::shared_ptr<SoundManager> m_soundManager;

};

