#pragma once

#include <GL/glew.h>

#include <GLFW/glfw3.h>

#include "camera.h"

#include "property/propertymanager.h"
#include "property/property.h"
#include "worldobject/ship.h"

class WorldObject;


class InputHandler {
public:
    InputHandler(GLFWwindow *window, Camera *camera);
	virtual ~InputHandler();

    void setPlayerShip(Ship *ship);


	void resizeEvent(const unsigned int width, const unsigned int height);
	void keyCallback(int key, int scancode, int action, int mods);
	void update(float delta_sec);

protected:

    void toggleControls();
    void fireGuns(double x, double y);

	GLFWwindow *m_window;
	Camera* m_camera;

    Ship *m_playerShip;


	int m_windowWidth, m_windowHeight;
	int m_lastfocus;

	int m_cursorMaxDistance;
	int m_fpsControls;
	int m_mouseControl;
	int m_mouseControlToggled;
    int m_followCam;


    Property<float> prop_rotationSpeed;
    Property<float> prop_rollSpeed;
    Property<float> prop_moveSpeed;
};
