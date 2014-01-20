#pragma once
#include <memory>

#include <glow/ref_ptr.h>
#include <glow/Texture.h>
#include <glow/Program.h>
#include <glow/VertexArrayObject.h>
#include <glow/Buffer.h>

#include <GLFW/glfw3.h>

#include "ui/inputhandler.h"
#include "ui/streamredirect.h"

#include "utils/timedtask.h"
#include "worldtree/worldtree.h"


class HUD;
class Skybox;
class World;
class InputHandler;
class VoxelRenderer;
class HD3000Dummy;
class LinuxVMDummy;
class Ship;
class Starfield;

class Game {

public:
    Game(GLFWwindow* window);
    virtual ~Game();
    void initialize();
    void reloadConfig();

    void update(float deltaSec);
    void draw();

    InputHandler* inputHandler();

private:
    void testFMOD();

private:
	GLFWwindow* m_window;
    Player m_player;
    Camera m_camera;

    World* m_world;

    std::unique_ptr<Skybox> m_skybox;
    std::unique_ptr<HUD> m_hud;
    std::unique_ptr<InputHandler> m_inputHandler;
    std::unique_ptr<HD3000Dummy> m_hd3000dummy;
    std::unique_ptr<LinuxVMDummy> m_linuxvmdummy;
    std::unique_ptr<Starfield> m_starfield;
    std::shared_ptr<VoxelRenderer> m_voxelRenderer;

    StreamRedirect* m_out;
    StreamRedirect* m_err;
};

