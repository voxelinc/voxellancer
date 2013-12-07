#include "inputhandler.h"

#include <glm/glm.hpp>

InputHandler::InputHandler(GLFWwindow *window, Camera *camera) :
    m_window(window),
    m_camera(camera),
    prop_rotationSpeed("input.rotationSpeed"),
    prop_moveSpeed("input.moveSpeed"),
    prop_rollSpeed("input.rollSpeed"),
    m_playerShip(nullptr),
    m_followCam(true)
{

	glfwGetWindowSize(m_window, &m_windowWidth, &m_windowHeight);
	glfwSetCursorPos(m_window, m_windowWidth / 2, m_windowHeight / 2);
	m_cursorMaxDistance = glm::min(m_windowHeight, m_windowWidth);

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
    if (key == GLFW_KEY_TAB && action == GLFW_PRESS)
        selectNextTarget();
}

void InputHandler::update(float delta_sec) {
	/* Check here for every-frame events, e.g. view & movement controls */
    if (glfwGetWindowAttrib(m_window, GLFW_FOCUSED)){
        if (m_lastfocus){
            // position voxelcluster

			if (glfwGetKey(m_window, GLFW_KEY_UP) == GLFW_PRESS){
                m_playerShip->accelerate(glm::vec3(0, 0, -prop_moveSpeed.get()));
			}
			if (glfwGetKey(m_window, GLFW_KEY_LEFT) == GLFW_PRESS){
                m_playerShip->accelerate(-glm::vec3(prop_moveSpeed.get(), 0, 0));
			}
			if (glfwGetKey(m_window, GLFW_KEY_DOWN) == GLFW_PRESS){
                m_playerShip->accelerate(glm::vec3(0, 0, prop_moveSpeed.get()));
			}
			if (glfwGetKey(m_window, GLFW_KEY_RIGHT) == GLFW_PRESS){
                m_playerShip->accelerate(glm::vec3(prop_moveSpeed.get(), 0, 0));
			}
			if (glfwGetKey(m_window, GLFW_KEY_PAGE_DOWN) == GLFW_PRESS){
                m_playerShip->accelerate(glm::vec3(0, -prop_moveSpeed.get(), 0));
			}
			if (glfwGetKey(m_window, GLFW_KEY_PAGE_UP) == GLFW_PRESS){
                m_playerShip->accelerate(glm::vec3(0, prop_moveSpeed.get(), 0));
			}

            if (glfwGetKey(m_window, GLFW_KEY_I) == GLFW_PRESS) {
                m_playerShip->accelerateAngular(glm::vec3(1, 0, 0));
            }
            if (glfwGetKey(m_window, GLFW_KEY_K) == GLFW_PRESS) {
                m_playerShip->accelerateAngular(glm::vec3(-1, 0, 0));
            }
            if (glfwGetKey(m_window, GLFW_KEY_J) == GLFW_PRESS) {
                m_playerShip->accelerateAngular(glm::vec3(0, 1, 0));
            }
            if (glfwGetKey(m_window, GLFW_KEY_L) == GLFW_PRESS) {
                m_playerShip->accelerateAngular(glm::vec3(0, -1, 0));
            }
            if (glfwGetKey(m_window, GLFW_KEY_U) == GLFW_PRESS) {
                m_playerShip->accelerateAngular(glm::vec3(0, 0, 1));
            }
            if (glfwGetKey(m_window, GLFW_KEY_O) == GLFW_PRESS) {
                m_playerShip->accelerateAngular(glm::vec3(0, 0, -1));
            }

            if (!m_followCam){ //disable view controls when cam is following

                // position "eye"
                if (glfwGetKey(m_window, GLFW_KEY_W) == GLFW_PRESS){
                    m_camera->move(glm::vec3(0, 0, -prop_moveSpeed* delta_sec));
                }
                if (glfwGetKey(m_window, GLFW_KEY_A) == GLFW_PRESS){
                    m_camera->move(glm::vec3(-prop_moveSpeed * delta_sec, 0, 0));
                }
                if (glfwGetKey(m_window, GLFW_KEY_S) == GLFW_PRESS){
                    m_camera->move(glm::vec3(0, 0, prop_moveSpeed* delta_sec));
                }
                if (glfwGetKey(m_window, GLFW_KEY_D) == GLFW_PRESS){
                    m_camera->move(glm::vec3(prop_moveSpeed* delta_sec, 0, 0));
                }
                if (glfwGetKey(m_window, GLFW_KEY_Q) == GLFW_PRESS){
                    m_camera->rotateZ(-prop_rollSpeed * delta_sec);
                }
                if (glfwGetKey(m_window, GLFW_KEY_E) == GLFW_PRESS){
                    m_camera->rotateZ(prop_rollSpeed * delta_sec);
                }

                // lookAt
                double x, y;
                glfwGetCursorPos(m_window, &x, &y);
                float rel = 10;
                float deadzone = 0.1f;
                if (!m_fpsControls) {
                    if (m_mouseControl || glfwGetMouseButton(m_window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS){
                        rel = (float)glm::max(1.0, (sqrt(pow(m_windowWidth - (int)floor(x), 2) + pow(m_windowHeight - (int)floor(y), 2))) / m_cursorMaxDistance);
                        rel = glm::max(0.0f, rel - deadzone) / (1 - deadzone);
                        rel = glm::smoothstep(0.f, 1.f, rel);
                    } else {
                        rel = 0;
                    }
                }

                float angX = ((int)floor(x) - m_windowWidth / 2) * prop_rotationSpeed * rel;
                float angY = ((int)floor(y) - m_windowHeight / 2) * prop_rotationSpeed * rel;

                m_camera->rotateX(-angY*delta_sec);
                m_camera->rotateY(-angX*delta_sec);
            }

            double x, y;
            glfwGetCursorPos(m_window, &x, &y);

            // shoot
            if (glfwGetMouseButton(m_window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS){
                if (m_playerShip->aimMode() == Point){
                    adjustAim(x, y);
                }
                m_playerShip->fire();
            }

			// lookAt
            float rel = 10;
            float deadzone = 0.05f;
            double dis = 0;
            float angX = 0;
            float angY = 0;

			if (!m_fpsControls) {
				if (m_mouseControl || glfwGetMouseButton(m_window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS){
                    x = m_windowWidth / 2 - (int)floor(x);
                    y = m_windowHeight / 2 - (int)floor(y);
                    dis = glm::min((sqrt(pow(x, 2) + pow(y, 2))), (double)m_cursorMaxDistance / 2);
                    rel = (float)(dis / (m_cursorMaxDistance / 2));

                    rel = glm::max(0.0f, rel - deadzone) / (1 - deadzone);
                    rel = glm::smoothstep(0.f, 1.f, rel);
                    angX = float(-x * prop_rotationSpeed * rel);
                    angY = float(-y * prop_rotationSpeed * rel);
				}
                else {
                    rel = 0;
				}
			}
            else {
                angX = ((int)floor(x) - m_windowWidth / 2) * prop_rotationSpeed * rel;
                angY = ((int)floor(y) - m_windowHeight / 2) * prop_rotationSpeed * rel;
			}

			m_camera->rotateX(-angY*delta_sec);
			m_camera->rotateY(-angX*delta_sec);

		}


        if (m_fpsControls)
            glfwSetCursorPos(m_window, m_windowWidth / 2, m_windowHeight / 2);

	}

    if (m_followCam){
        m_camera->setPosition(m_playerShip->transform().position());
        m_camera->move(glm::vec3(0, 5, 10));
        m_camera->setOrientation(m_playerShip->transform().orientation());
    }

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


void InputHandler::setPlayerShip(Ship* ship) {
    m_playerShip = ship;
    m_playerShip->setAimMode(Point);
}

void InputHandler::selectNextTarget(){
    std::list<WorldObject*>& worldObjects = World::instance()->worldObjects();
    std::list<WorldObject*>::iterator newTarget = worldObjects.end();

    if (m_playerShip->aimMode() == Point){
        m_playerShip->setAimMode(Object);
        newTarget = worldObjects.begin();
    } else if (m_playerShip->aimMode() == Object){
        std::list<WorldObject*>::iterator iterator = worldObjects.begin();
        while (iterator != worldObjects.end()){
            if (*iterator == m_playerShip->targetObject()){
                newTarget = ++iterator;
                break;
            }
            ++iterator;
        }
    }
    if (newTarget == worldObjects.end()){
        m_playerShip->setAimMode(Point);
    } else {
        // newTarget points to next target, which might not be lockable
        // find first lockable target
        std::list<WorldObject*>::iterator iterator = newTarget;
        while (iterator != worldObjects.end()){
            if ((*iterator)->objectInfo().canLockOn()){
                m_playerShip->setAimMode(Object);
                m_playerShip->setTargetObject(*newTarget);
                return;
            }
            ++iterator;
        }
        // reach here if no lockable target left, then switch back to Point-Aiming
        m_playerShip->setAimMode(Point);
    }
}

std::string InputHandler::playerTarget(){
    if (m_playerShip->aimMode() == Point)
        return "Guns";
    if (m_playerShip->aimMode() == Object)
        if (m_playerShip->targetObject())
            return "Locked: " + m_playerShip->targetObject()->objectInfo().name();
        else
            return "Invalid Lock";
    return "-";
}

void InputHandler::adjustAim(double x, double y){
    glm::vec4 pointEnd((x * 2 / m_windowWidth - 1), -1 * (y * 2 / m_windowHeight - 1), 1, 1); //get normalized device coords
    pointEnd = glm::inverse(m_camera->viewProjection())*pointEnd; //find point on zfar
    glm::vec3 vec = glm::vec3(pointEnd); // no need for w component
    vec = glm::normalize(vec); // normalize
    vec *= m_playerShip->minAimDistance(); // set aimdistance
    vec += m_camera->position(); //adjust for camera translation
    m_playerShip->setTargetPoint(vec);
}
