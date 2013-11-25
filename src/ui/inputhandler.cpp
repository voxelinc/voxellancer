#include "inputhandler.h"

#include <glm/glm.hpp>

#include "world/physicalvoxelcluster.h"



InputHandler::InputHandler(GLFWwindow *window, Camera *camera, PhysicalVoxelCluster *voxelcluster):
	m_window(window),
	m_camera(camera),
	m_voxelcluster(voxelcluster),
	m_rotation_speed("input.rotation_speed"),
    m_move_speed("input.move_speed"),
    m_roll_speed("input.roll_speed")
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
}

void InputHandler::update(float delta_sec) {
	/* Check here for every-frame events, e.g. view & movement controls */

	if (glfwGetWindowAttrib(m_window, GLFW_FOCUSED)){
		if (m_lastfocus){

			// position "eye"
			if (glfwGetKey(m_window, GLFW_KEY_W) == GLFW_PRESS){
				m_camera->move(glm::vec3(0, 0, -m_move_speed* delta_sec));
			}
			if (glfwGetKey(m_window, GLFW_KEY_A) == GLFW_PRESS){
				m_camera->move(glm::vec3(-m_move_speed * delta_sec, 0, 0));
			}
			if (glfwGetKey(m_window, GLFW_KEY_S) == GLFW_PRESS){
				m_camera->move(glm::vec3(0, 0, m_move_speed* delta_sec));
			}
			if (glfwGetKey(m_window, GLFW_KEY_D) == GLFW_PRESS){
				m_camera->move(glm::vec3(m_move_speed* delta_sec, 0, 0));
			}
			if (glfwGetKey(m_window, GLFW_KEY_Q) == GLFW_PRESS){
				m_camera->rotateZ(-m_roll_speed * delta_sec);
			}
			if (glfwGetKey(m_window, GLFW_KEY_E) == GLFW_PRESS){
                m_camera->rotateZ(m_roll_speed * delta_sec);
			}

            // position voxelcluster
			if (glfwGetKey(m_window, GLFW_KEY_UP) == GLFW_PRESS){
                m_voxelcluster->accelerate(glm::vec3(0, 0, -m_move_speed.get()));
			}
			if (glfwGetKey(m_window, GLFW_KEY_LEFT) == GLFW_PRESS){
                m_voxelcluster->accelerate(-glm::vec3(m_move_speed.get(), 0, 0));
			}
			if (glfwGetKey(m_window, GLFW_KEY_DOWN) == GLFW_PRESS){
                m_voxelcluster->accelerate(glm::vec3(0, 0, m_move_speed.get()));
			}
			if (glfwGetKey(m_window, GLFW_KEY_RIGHT) == GLFW_PRESS){
                m_voxelcluster->accelerate(glm::vec3(m_move_speed.get(), 0, 0));
			}
			if (glfwGetKey(m_window, GLFW_KEY_PAGE_DOWN) == GLFW_PRESS){
                m_voxelcluster->accelerate(glm::vec3(0, -m_move_speed.get(), 0));
			}
			if (glfwGetKey(m_window, GLFW_KEY_PAGE_UP) == GLFW_PRESS){
                m_voxelcluster->accelerate(glm::vec3(0, m_move_speed.get(), 0));
			}
            if (glfwGetKey(m_window, GLFW_KEY_I) == GLFW_PRESS) {
                m_voxelcluster->accelerate_angular(glm::vec3(1, 0, 0));
            }
            if (glfwGetKey(m_window, GLFW_KEY_K) == GLFW_PRESS) {
                m_voxelcluster->accelerate_angular(glm::vec3(-1, 0, 0));
            }
            if (glfwGetKey(m_window, GLFW_KEY_J) == GLFW_PRESS) {
                m_voxelcluster->accelerate_angular(glm::vec3(0, 1, 0));
            }
            if (glfwGetKey(m_window, GLFW_KEY_L) == GLFW_PRESS) {
                m_voxelcluster->accelerate_angular(glm::vec3(0, -1, 0));
            }

            if (glfwGetKey(m_window, GLFW_KEY_M) == GLFW_PRESS) {
                m_camera->setPosition(m_voxelcluster->transform().position());
                m_camera->move(glm::vec3(0, 2, 10));
                m_camera->setOrientation(m_voxelcluster->transform().orientation());
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
				}
				else {
					rel = 0;
				}
			}

			float angX = ((int)floor(x) - m_windowWidth / 2) * m_rotation_speed * rel;
			float angY = ((int)floor(y) - m_windowHeight / 2) * m_rotation_speed * rel;

			m_camera->rotateX(-angY*delta_sec);
			m_camera->rotateY(-angX*delta_sec);

		}

		if (m_fpsControls)
			glfwSetCursorPos(m_window, m_windowWidth / 2, m_windowHeight / 2);

	}

	m_lastfocus = glfwGetWindowAttrib(m_window, GLFW_FOCUSED);
}

void InputHandler::toggleControls()
{
	if (m_fpsControls)
	{
		glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	}
	else
	{
		glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
	}
	m_fpsControls = !m_fpsControls;
}
