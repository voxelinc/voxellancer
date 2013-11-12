#pragma once
#include <memory>

#include <glow/ref_ptr.h>
#include <glow/Texture.h>
#include <glow/Program.h>
#include <glow/VertexArrayObject.h>
#include <glow/Buffer.h>

#include <GLFW/glfw3.h>

#include "camera.h"
#include "skybox.h"

#include "voxel/voxelcluster.h"

#include "worldtree/worldtree.h"

#include "collision/collisiondetector.h"

#include "inputhandler.h"


class InputHandler;
class VoxelCluster;
class VoxelRenderer;
class HD3000Dummy;


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
	Skybox m_skybox;
    VoxelCluster m_testCluster;
    VoxelCluster m_testClusterMoveable;
    Worldtree m_worldtree;
    CollisionDetector m_collisionDetector;
    std::unique_ptr<VoxelRenderer> m_voxelRenderer;
    std::unique_ptr<HD3000Dummy> m_hd3000dummy;
};

