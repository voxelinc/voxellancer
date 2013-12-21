#include "inputhandler.h"

#include <glm/glm.hpp>
#include <glow/glow.h>

#include "voxeleffect/voxelexplosiongenerator.h"

/*
* 360 gamepad assignment: (direction given for positive values)
* - A0: left stick right                        move right
* - A1: left stick up                           move forward
* - A2: left trigger (right trigger is [-1, 0]  -1 = gun trigger, +1 = rocket trigger
* - A3: right stick down(!)                     rotate down
* - A4: right stick right                       rotate up
*/

/*
* Button assignment
* B0: A
* B1: B
* B2: X
* B3: Y
* B4: left bumper               --previous target
* B5: right bumper              next target
* B6: back
* B7: start
* B8: left stick
* B9: right stick
*/


InputHandler::InputHandler(GLFWwindow *window, Player* player, Camera *camera) :
m_window(window),
m_player(player),
m_camera(camera),
prop_deadzoneMouse("input.deadzoneMouse"),
prop_deadzoneGamepad("input.deadzoneGamepad"),
m_targeter(new Targeter(player, camera))
{
    bumperLeftState = false;
    bumperRightState = false;
    glfwGetWindowSize(m_window, &m_windowWidth, &m_windowHeight);
    glfwSetCursorPos(m_window, m_windowWidth / 2, m_windowHeight / 2);

    m_cursorMaxDistance = glm::min(m_windowHeight, m_windowWidth) / 2;

    m_mouseControl = false;
    m_lastfocus = glfwGetWindowAttrib(m_window, GLFW_FOCUSED);

    glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}

InputHandler::~InputHandler(){

}

void InputHandler::resizeEvent(const unsigned int width, const unsigned int height){
	//glfwGetWindowSize(m_window, &m_windowWidth, &m_windowHeight);
	m_windowWidth = width;
	m_windowHeight = height;
	m_camera->setViewport(glm::ivec2(m_windowWidth, m_windowHeight));
	m_lastfocus = false; // through window resize everything becomes scrambled
}

void InputHandler::keyCallback(int key, int scancode, int action, int mods){
	/* Check here for single-time key-presses, that you do not want fired multiple times, e.g. toggles */
    if (key == GLFW_KEY_SPACE && action == GLFW_PRESS)
        m_mouseControl = !m_mouseControl;
    if (key == GLFW_KEY_TAB && action == GLFW_PRESS){
        if (glfwGetKey(m_window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
            m_targeter->selectNextTarget();
        else
            m_targeter->selectPreviousTarget();
    }
    if (key == GLFW_KEY_B && action == GLFW_PRESS){
        VoxelExplosionGenerator g;
        g.setPosition(m_player->playerShip()->transform().position() + m_player->playerShip()->transform().orientation() * glm::vec3(0, 0, -30));
        g.setOrientation(m_player->playerShip()->transform().orientation());
        g.setScale((float)(rand() % 3) + 1);
        g.setForce((float)(rand() % 2) + 1);
        g.setDensity((rand() % 4) + 2);
        g.spawn();
    }
}

void InputHandler::update(float delta_sec) {
	/* Check here for every-frame events, e.g. view & movement controls */
    if (glfwGetWindowAttrib(m_window, GLFW_FOCUSED)){
        if (m_lastfocus){
			if (glfwGetKey(m_window, GLFW_KEY_PAGE_DOWN) == GLFW_PRESS){
                m_player->move(glm::vec3(0, -1, 0));
			}
			if (glfwGetKey(m_window, GLFW_KEY_PAGE_UP) == GLFW_PRESS){
                m_player->move(glm::vec3(0, 1, 0));
			}
            if (glfwGetKey(m_window, GLFW_KEY_W) == GLFW_PRESS){
                m_player->move(glm::vec3(0, 0, -1));
            }
            if (glfwGetKey(m_window, GLFW_KEY_A) == GLFW_PRESS){
                m_player->move(-glm::vec3(1, 0, 0));
            }
            if (glfwGetKey(m_window, GLFW_KEY_S) == GLFW_PRESS){
                m_player->move(glm::vec3(0, 0, 1));
            }
            if (glfwGetKey(m_window, GLFW_KEY_D) == GLFW_PRESS){
                m_player->move(glm::vec3(1, 0, 0));
            }
            if (glfwGetKey(m_window, GLFW_KEY_Q) == GLFW_PRESS){
                m_player->rotate(glm::vec3(0, 0, 1));
            }
            if (glfwGetKey(m_window, GLFW_KEY_E) == GLFW_PRESS){
                m_player->rotate(glm::vec3(0, 0, -1));
            }
            if (glfwGetKey(m_window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS){
                m_player->boost();
            }
            if (glfwGetKey(m_window, GLFW_KEY_E) == GLFW_PRESS){
                m_player->rotate(glm::vec3(0, 0, -1));
            }

            if (glfwJoystickPresent(GLFW_JOYSTICK_1)) {
                // Button mapping
                int cnt = 0;
                int cntAxes = 0;
                const unsigned char *buttons = glfwGetJoystickButtons(GLFW_JOYSTICK_1, &cnt);
                const float *axes = glfwGetJoystickAxes(GLFW_JOYSTICK_1, &cntAxes);


                if (buttons[4] == GLFW_PRESS){
                    if (!bumperLeftState)
                        m_targeter->selectPreviousTarget();
                    bumperLeftState = true;
                } else {
                    bumperLeftState = false;
                }
                if (buttons[5] == GLFW_PRESS){
                    if (!bumperRightState)
                        m_targeter->selectNextTarget();
                    bumperRightState = true;
                } else {
                    bumperRightState = false;
                }
                if (glm::abs(axes[2]) > prop_deadzoneGamepad){
                    if (axes[2] < 0)
                        m_player->playerShip()->fireAtPoint(findTargetPoint(m_windowWidth / 2, m_windowHeight / 2));
                    else
                        m_player->playerShip()->fireAtObject();
                }
                if (glm::abs(axes[0]) > prop_deadzoneGamepad){
                    m_player->move(glm::vec3(axes[0], 0, 0));
                }
                if (glm::abs(axes[1]) > prop_deadzoneGamepad){
                    m_player->move(glm::vec3(0, 0, -axes[1]));
                }
                glm::vec3 rot = glm::vec3(0);
                if (glm::abs(axes[3]) > prop_deadzoneGamepad){
                    rot.x = -axes[3];
                }
                if (glm::abs(axes[4]) > prop_deadzoneGamepad){
                    rot.y = -axes[4];
                }
                if (glm::length(rot) < prop_deadzoneGamepad){
                    rot = glm::vec3(0);
                }
                if (glm::length(rot) > 1){
                    rot = glm::normalize(rot);
                }
                m_player->rotate(rot);
            }

            // mouse handling
            double x, y;
            glfwGetCursorPos(m_window, &x, &y);

            // shoot
            if (glfwGetMouseButton(m_window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS){
                m_player->playerShip()->fireAtPoint(findTargetPoint(x, y));
            }
            if (glfwGetKey(m_window, GLFW_KEY_R) == GLFW_PRESS){
                m_player->playerShip()->fireAtObject();
            }

			// lookAt
            float rel = 20;
            double dis = 0;
            float angX = 0;
            float angY = 0;

            if (m_mouseControl || glfwGetMouseButton(m_window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS){
                glm::vec3 rot;
                x = m_windowWidth / 2 - (int)floor(x);
                y = m_windowHeight / 2 - (int)floor(y);
                x = glm::min((double)m_cursorMaxDistance, x);
                y = glm::min((double)m_cursorMaxDistance, y);
                rot = glm::vec3(y, x, 0);
                rot /= m_cursorMaxDistance;

                if (glm::length(rot) < prop_deadzoneMouse){
                    rot = glm::vec3(0);
                }
                if (glm::length(rot) > 1){
                    rot = glm::normalize(rot);
                }
                m_player->rotate(rot);

            }
        }
    }

    m_player->applyAcceleration();

	m_lastfocus = glfwGetWindowAttrib(m_window, GLFW_FOCUSED);
}



glm::vec3 InputHandler::findTargetPoint(double x, double y){
    glm::vec4 pointEnd((x * 2 / m_windowWidth - 1), -1 * (y * 2 / m_windowHeight - 1), 1, 1); //get normalized device coords
    pointEnd = glm::inverse(m_camera->viewProjection())*pointEnd; //find point on zfar
    glm::vec3 vec = glm::vec3(pointEnd); // no need for w component
    vec = glm::normalize(vec); // normalize
    vec *= m_player->playerShip()->minAimDistance(); // set aimdistance
    vec += m_camera->position(); //adjust for camera translation
    return vec;
}
