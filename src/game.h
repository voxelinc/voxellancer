#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "etc/hmd/hmdmanager.h"

#include "render/viewer.h"
#include "render/gamescene.h"

#include "ui/inputhandler.h"

#include "player.h"


class Game {
public:
    Game();

    InputHandler& inputHandler();
    Player& player();
    Viewer& viewer();
    HMDManager& hmdManager();

    void initialize();

    void update(float deltaSec);
    void draw();


private:
	InputHandler m_inputHandler;
    Player m_player;
    Viewer m_viewer;
    GameScene m_gameScene;
    HMDManager m_hmdManager;
};

