#pragma once
#include <memory>

#include <glow/ref_ptr.h>
#include <glow/Texture.h>
#include <glow/Program.h>
#include <glow/VertexArrayObject.h>
#include <glow/Buffer.h>

#include <GLFW/glfw3.h>

#include "camera/cameradolly.h"

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


class Game {
public:
    Game(GLFWwindow* window);

    void initialize();
    void reloadConfig();

    void update(float deltaSec);
    void draw();

    InputHandler& inputHandler();


private:
	GLFWwindow* m_window;

    World* m_world;
	InputHandler m_inputHandler;
    Player m_player;

    StreamRedirect* m_out;
    StreamRedirect* m_err;
};

