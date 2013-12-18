#pragma once
#include <memory>

#include <glow/ref_ptr.h>
#include <glow/Texture.h>
#include <glow/Program.h>
#include <glow/VertexArrayObject.h>
#include <glow/FrameBufferObject.h>
#include <glow/RenderBufferObject.h>
#include <glow/VertexAttributeBinding.h>
#include <glowutils/ScreenAlignedQuad.h>
#include <glow/Buffer.h>
#include <glow/glow.h>
#include <glowutils/glowutils.h>
#include <glowutils/File.h>

#include <GLFW/glfw3.h>

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

    void update(float delta_sec);
	void draw();

    InputHandler * inputHandler();

private:
    void testFMOD();

private:
	GLFWwindow *m_window;
	InputHandler m_inputHandler;
    Player m_player;
	Camera m_camera;

    World * m_world;

    glow::ref_ptr<glow::FrameBufferObject> m_fboGameDepth;
    glow::ref_ptr<glow::RenderBufferObject> m_bufferGameDepth;
    glow::ref_ptr<glow::Buffer> m_buffer;


	std::unique_ptr<Skybox> m_skybox;
	std::unique_ptr<HUD> m_hud;
	std::unique_ptr<VoxelRenderer> m_voxelRenderer;
	std::unique_ptr<HD3000Dummy> m_hd3000dummy;
	std::unique_ptr<LinuxVMDummy> m_linuxvmdummy;

    TreeStateReporter m_treeStateReporter;
};

