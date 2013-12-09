#include "inputhandler.h"

#include <glm/glm.hpp>
#include <glow/glow.h>

InputHandler::InputHandler(GLFWwindow *window, Camera *camera) :
m_window(window),
m_camera(camera),
prop_rotationSpeed("input.rotationSpeed"),
prop_moveSpeed("input.moveSpeed"),
prop_rollSpeed("input.rollSpeed"),
m_followCam(true)
{

    glfwGetWindowSize(m_window, &m_windowWidth, &m_windowHeight);
    glfwSetCursorPos(m_window, m_windowWidth / 2, m_windowHeight / 2);
    m_cursorMaxDistance = glm::min(m_windowHeight, m_windowWidth)/2;

    m_fpsControls = false;
    m_mouseControl = false;
    m_lastfocus = glfwGetWindowAttrib(m_window, GLFW_FOCUSED);

    glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}

InputHandler::InputHandler(GLFWwindow *window, Player* player, Camera *camera) :
m_window(window),
m_player(player),
m_camera(camera),
prop_rotationSpeed("input.rotationSpeed"),
prop_moveSpeed("input.moveSpeed"),
prop_rollSpeed("input.rollSpeed"),
m_followCam(true)
{

    glfwGetWindowSize(m_window, &m_windowWidth, &m_windowHeight);
    glfwSetCursorPos(m_window, m_windowWidth / 2, m_windowHeight / 2);
    m_cursorMaxDistance = glm::min(m_windowHeight, m_windowWidth)/2;

    m_fpsControls = false;
    m_mouseControl = false;
    m_lastfocus = glfwGetWindowAttrib(m_window, GLFW_FOCUSED);

    glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}

InputHandler::~InputHandler(){

}


void InputHandler::resizeEvent(
	const unsigned int width
	, const unsigned int height)
{
	//glfwGetWindowSize(m_window, &m_windowWidth, &m_windowHeight);
	m_windowWidth = width;
	m_windowHeight = height;
	m_camera->setViewport(glm::ivec2(m_windowWidth, m_windowHeight));
	m_lastfocus = false; // through window resize, everything becomes scrambled
}

void InputHandler::keyCallback(int key, int scancode, int action, int mods){
	/* Check here for single-time key-presses, that you do not want fired multiple times, e.g. toggles */
	if (key == GLFW_KEY_F1 && action == GLFW_PRESS)
		toggleControls();
	if (key == GLFW_KEY_SPACE && action == GLFW_PRESS)
		m_mouseControl = !m_mouseControl;
    if (key == GLFW_KEY_M && action == GLFW_PRESS)
        m_followCam = !m_followCam;
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

            // mouse handling
            double x, y;
            glfwGetCursorPos(m_window, &x, &y);

            // shoot
            if (glfwGetMouseButton(m_window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS){
                shoot(x, y);
            }

			// lookAt
            float rel = 20;
            float deadzone = 0.1f;
            double dis = 0;
            float angX = 0;
            float angY = 0;

			if (!m_fpsControls) {
				if (m_mouseControl || glfwGetMouseButton(m_window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS){
                    glm::vec3 rot;
                    x = m_windowWidth / 2 - (int)floor(x);
                    y = m_windowHeight / 2 - (int)floor(y);
                    x = glm::min((double)m_cursorMaxDistance, x);
                    y = glm::min((double)m_cursorMaxDistance, y);
                    rot = glm::vec3(y,x, 0);
                    rot /= m_cursorMaxDistance;
                    printf("%f %f\n", rot.y, rot.x);
                    if (glm::length(rot) < deadzone)
                        rot = glm::vec3(0);
                    if (glm::length(rot) > 1){
                        rot = glm::normalize(rot);
                    }
                    m_player->rotate(rot);
				}
                else {
                    rel = 0;
                }
			}
            else {
                angX = ((int)floor(x) - m_windowWidth / 2) * rel;
                angY = ((int)floor(y) - m_windowHeight / 2) * rel;
            }

		}


        if (m_fpsControls)
            glfwSetCursorPos(m_window, m_windowWidth / 2, m_windowHeight / 2);

    }

    if (m_followCam){
        m_player->setFollowCam();
    }
    else{
        m_player->setShipToCam(delta_sec);
    }

    /*
    float z;
    glReadPixels((int)0, (int)0, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &z);
    printf("%f orig\n", z);
    z = 2 * m_camera->zNear()*m_camera->zFar() / (m_camera->zFar() + m_camera->zNear() - (2 * z - 1)* (m_camera->zFar() - m_camera->zNear()));
    printf("%f\n", z);
    */
	m_lastfocus = glfwGetWindowAttrib(m_window, GLFW_FOCUSED);
}

void InputHandler::toggleControls()
{
	if (m_fpsControls) {
		glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	}
	else {
		glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
	}
	m_fpsControls = !m_fpsControls;
}


void InputHandler::shoot(double x, double y){
    glm::vec4 pointEnd((x * 2 / m_windowWidth - 1), -1 * (y * 2 / m_windowHeight - 1), 1, 1); //get normalized device coords
    pointEnd = glm::inverse(m_camera->viewProjection())*pointEnd; //find point on zfar
    glm::vec3 vec = glm::vec3(pointEnd); // no need for w component
    vec = glm::normalize(vec); // normalize
    vec *= m_player->playerShip()->minAimDistance(); // set aimdistance
    vec += m_camera->position(); //adjust for camera translation
    m_player->playerShip()->shootAt(vec);
}
