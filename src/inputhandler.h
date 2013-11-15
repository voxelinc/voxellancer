#pragma once

#include <GLFW/glfw3.h>

#include "camera.h"

#include "property/propertymanager.h"
#include "property/property.h"

class InputHandler {
public:
	InputHandler(GLFWwindow *window, Camera *camera);
	virtual ~InputHandler();

	void resizeEvent(const unsigned int width, const unsigned int height);
	void keyCallback(int key, int scancode, int action, int mods);
	void update(float delta_sec);

protected:
	GLFWwindow *m_window;
	Camera* m_camera;

	int m_windowWidth, m_windowHeight;
	int m_lastfocus;

	int m_cursorMaxDistance;
	int m_fpsControls;
	int m_mouseControl;
	int m_mouseControlToggled;

	Property<float> m_angle_translate;
	Property<float> m_move_translate;
	
	void toggleControls();
};
