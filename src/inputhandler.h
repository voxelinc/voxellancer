#pragma once

#include <GLFW/glfw3.h>

#include "camera.h"

#include "property/property.h"

class InputHandler {
public:
	InputHandler(GLFWwindow *window, Camera *camera);
	virtual ~InputHandler();

	void resizeEvent(const unsigned int width, const unsigned int height);
	void update(float delta_sec);
	void toggleControls();

protected:
	GLFWwindow *m_window;
	Camera* m_camera;

	int m_windowWidth, m_windowHeight;

	int m_cursorMaxDistance;
	int m_fpsControls;

//	Property<float> m_angle_translate;
//	Property<float> m_move_translate;
	float m_angle_translate;
	float m_move_translate;
};
