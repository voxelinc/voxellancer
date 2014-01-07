#pragma once

#include <GL/glew.h>

#include <GLFW/glfw3.h>

#include "property/propertymanager.h"
#include "property/property.h"
#include "worldobject/ship.h"
#include "player.h"

class WorldObject;

// TODO: extract a Player from the inputhandler

class InputHandler {
public:
    InputHandler(GLFWwindow *window, Camera *camera);
    InputHandler(GLFWwindow *window, Player *player, Camera *camera);
	virtual ~InputHandler();

	void resizeEvent(const unsigned int width, const unsigned int height);
	void keyCallback(int key, int scancode, int action, int mods);
	void update(float deltaSec);

protected:

    void toggleControls();
    WorldObject* findNextTarget(bool forward);
    void selectNextTarget(bool forward);
    glm::vec3 findTargetPoint(double x, double y);

    bool bumperLeftState, bumperRightState;

	GLFWwindow *m_window;
	Camera* m_camera;
    Player* m_player;


	int m_windowWidth, m_windowHeight;
	int m_lastfocus;

	int m_cursorMaxDistance;
	int m_mouseControl;

    Property<float> prop_deadzone;

};
