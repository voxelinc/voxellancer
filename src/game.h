#pragma once

#include "glow/ref_ptr.h"
#include "glow/Texture.h"
#include "glow/Program.h"
#include "glow/VertexArrayObject.h"
#include "glow/Buffer.h"

#include <GLFW/glfw3.h>

#include "camera.h"
#include "skybox.h"
#include "cube.h"

class Game {

public:
    Game(GLFWwindow *window);
	void initialize();


    void update(float delta_sec);
	void draw();
	void resizeEvent(const unsigned int width, const unsigned int height);
	void toggleControls();

private:
    void testFMOD();

private:
	GLFWwindow *m_window;
	Camera m_camera;
	Skybox m_skybox;
    Cube *m_cube;

	int cursorMaxDistance, windowWidth, windowHeight;
	int fpsControls;

	static const float s_angle_translate;
	static const float s_move_translate;
};