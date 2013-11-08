#pragma once

#include "glow/ref_ptr.h"
#include "glow/Texture.h"
#include "glow/Program.h"
#include "glow/VertexArrayObject.h"
#include "glow/Buffer.h"

#include <GLFW/glfw3.h>

#include "utils/hd3000dummy.h"
#include "inputhandler.h"
#include "camera.h"
#include "skybox.h"
#include "cube.h"

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
    HD3000Dummy m_hd3000dummy;

};