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

class TreeStateReporter : public TimedTask
{
public:
    TreeStateReporter();

    void setWorldTree(WorldTree *worldTree);

    virtual void exec();

protected:
    WorldTree *m_worldTree;
};

class Game {

public:
	Game(GLFWwindow *window);
	virtual ~Game();
	void initialize();
	void reloadConfig();

    Skybox* skybox();

    void update(float deltaSec);
	void draw();

    InputHandler * inputHandler();


private:
    void testFMOD();


private:
	GLFWwindow* m_window;
    World* m_world;
	InputHandler m_inputHandler;
    Player m_player;
	CameraDolly m_cameraDolly;


	std::unique_ptr<Skybox> m_skybox;
	std::unique_ptr<HUD> m_hud;
	std::unique_ptr<VoxelRenderer> m_voxelRenderer;
	std::unique_ptr<HD3000Dummy> m_hd3000dummy;
	std::unique_ptr<LinuxVMDummy> m_linuxvmdummy;

    TreeStateReporter m_treeStateReporter;
};

