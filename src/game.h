#pragma once

#include "glow/ref_ptr.h"
#include "glow/Texture.h"
#include "glow/Program.h"
#include "glow/VertexArrayObject.h"
#include "glow/Buffer.h"

#include <GLFW/glfw3.h>

#include "utils/hd3000dummy.h"
#include "camera.h"
#include "skybox.h"

class InputHandler;
class VoxelCluster;
class VoxelRenderer;

class Game {

public:
	Game(GLFWwindow *window);
	virtual ~Game();
	void initialize();
	void reloadConfig();

    void update(float delta_sec);
	void draw();

	InputHandler *m_inputHandler;

private:
    void testFMOD();

private:
	GLFWwindow *m_window;
	Camera m_camera;
	Skybox m_skybox;
    VoxelRenderer *m_voxelRenderer;
    VoxelCluster *m_testCluster;
    HD3000Dummy m_hd3000dummy;

};
