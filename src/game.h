#pragma once
#include <memory>

#include <glow/ref_ptr.h>
#include <glow/Texture.h>
#include <glow/Program.h>
#include <glow/VertexArrayObject.h>
#include <glow/Buffer.h>

#include <GLFW/glfw3.h>

#include "worldtree/worldtree.h"
#include "collision/collisiondetector.h"
#include "camera.h"
#include "ui/inputhandler.h"


class HUD;
class Skybox;
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
	std::vector<std::unique_ptr<VoxelCluster>> m_perf_clusterArmy;
	Property<int> m_perf_clusterArmySize;
	Property<bool> m_perf_draw, m_perf_apply, m_perf_test;
    Worldtree m_worldtree;
    CollisionDetector m_collisionDetector;
	std::unique_ptr<Skybox> m_skybox;
	std::unique_ptr<HUD> m_hud;
	std::unique_ptr<VoxelRenderer> m_voxelRenderer;
	std::unique_ptr<HD3000Dummy> m_hd3000dummy;
	std::unique_ptr<LinuxVMDummy> m_linuxvmdummy;
};

