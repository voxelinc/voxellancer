#pragma once
#include <memory>

#include <glow/ref_ptr.h>
#include <glow/Texture.h>
#include <glow/Program.h>
#include <glow/VertexArrayObject.h>
#include <glow/Buffer.h>

#include <GLFW/glfw3.h>

#include "voxel/voxelcluster.h"
#include "worldtree/worldtree.h"
#include "collision/collisiondetector.h"
#include "camera.h"
#include "skybox.h"
#include "inputhandler.h"


class HUD;
class InputHandler;
class VoxelCluster;
class VoxelRenderer;
class HD3000Dummy;
class LinuxVMDummy;


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
	Camera m_camera;
    VoxelCluster m_testCluster;
	VoxelCluster m_testClusterMoveable;
	VoxelCluster *m_testClusterA, *m_testClusterB;
    Worldtree m_worldtree;
    CollisionDetector m_collisionDetector;
	std::unique_ptr<Skybox> m_skybox;
	std::unique_ptr<HUD> m_hud;
	std::unique_ptr<VoxelRenderer> m_voxelRenderer;
	std::unique_ptr<HD3000Dummy> m_hd3000dummy;
	std::unique_ptr<LinuxVMDummy> m_linuxvmdummy;
};

