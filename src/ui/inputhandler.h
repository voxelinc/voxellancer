#pragma once

#include <GL/glew.h>

#include <GLFW/glfw3.h>

#include "camera/cameradolly.h"
#include "property/propertymanager.h"
#include "property/property.h"
#include "ui/crosshair.h"
#include "worldobject/ship.h"
#include "player.h"

class WorldObject;

// TODO: extract a Player from the inputhandler

class InputHandler {
public:
    InputHandler(GLFWwindow *window, Player *player);
	virtual ~InputHandler();

	void resizeEvent(const unsigned int width, const unsigned int height);
	void keyCallback(int key, int scancode, int action, int mods);
	void update(float deltaSec);


protected:
    void toggleControls();
    WorldObject* findNextTarget(bool forward);
    void selectNextTarget(bool forward);

    bool bumperLeftState, bumperRightState;

	GLFWwindow *m_window;
    Player* m_player;

	int m_windowWidth, m_windowHeight;
	int m_lastfocus;

	int m_cursorMaxDistance;
	int m_mouseControl;

    Property<float> prop_deadzone;

    glm::vec3 findTargetPoint();
    void placeCrossHair(double winX, double winY);
};
