#pragma once

#include <GL/glew.h>

#include <GLFW/glfw3.h>

#include "camera.h"

#include "property/propertymanager.h"
#include "property/property.h"

class WorldObject;


class InputHandler {
public:
    InputHandler(GLFWwindow *window, Camera *camera);
	virtual ~InputHandler();

    void setWorldObject(WorldObject *worldObject);

	void resizeEvent(const unsigned int width, const unsigned int height);
	void keyCallback(int key, int scancode, int action, int mods);
	void update(float delta_sec);

protected:
	GLFWwindow *m_window;
	Camera* m_camera;
    WorldObject *m_worldObject;

	int m_windowWidth, m_windowHeight;
	int m_lastfocus;

	int m_cursorMaxDistance;
	int m_fpsControls;
	int m_mouseControl;
	int m_mouseControlToggled;

    Property<float> m_rotation_speed;
    Property<float> m_roll_speed;
	Property<float> m_move_speed;

	void toggleControls();
};
