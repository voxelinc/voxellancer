#pragma once

#include "glow/ref_ptr.h"
#include "glow/Texture.h"
#include "glow/Program.h"
#include "glow/VertexArrayObject.h"
#include "glow/Buffer.h"

#include <GLFW/glfw3.h>

#include "voxel/cube.h"
#include "inputhandler.h"
#include "camera.h"
#include "skybox.h"
#include "clusterloader.h"

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
    Cube *m_cube;
    Voxelcluster m_testCluster;

};