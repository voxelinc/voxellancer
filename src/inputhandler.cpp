#include "inputhandler.h"

#include <glm/glm.hpp>



InputHandler::InputHandler(GLFWwindow *window, Camera *camera) :
	m_window(window),
	m_camera(camera),
	m_angle_translate("input.angle_translate", 0.15f),
	m_move_translate("input.move_translate", 3.0f)
{

	glfwGetWindowSize(m_window, &m_windowWidth, &m_windowHeight);
	glfwSetCursorPos(m_window, m_windowWidth / 2, m_windowHeight / 2);
	m_cursorMaxDistance = glm::min(m_windowHeight, m_windowWidth);

	m_fpsControls = true;
	m_lastfocus = glfwGetWindowAttrib(m_window, GLFW_FOCUSED);

	glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
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

void InputHandler::update(float delta_sec){

	if (glfwGetWindowAttrib(m_window, GLFW_FOCUSED)){
		if (m_lastfocus){

			// position "eye"
			if (glfwGetKey(m_window, GLFW_KEY_W) == GLFW_PRESS){
				m_camera->move(glm::vec3(0, 0, -m_move_translate* delta_sec));
			}
			if (glfwGetKey(m_window, GLFW_KEY_A) == GLFW_PRESS){
				m_camera->move(glm::vec3(-m_move_translate * delta_sec, 0, 0));

			}
			if (glfwGetKey(m_window, GLFW_KEY_S) == GLFW_PRESS){
				m_camera->move(glm::vec3(0, 0, m_move_translate* delta_sec));

			}
			if (glfwGetKey(m_window, GLFW_KEY_D) == GLFW_PRESS){
				m_camera->move(glm::vec3(m_move_translate* delta_sec, 0, 0));
			}
			if (glfwGetKey(m_window, GLFW_KEY_Q) == GLFW_PRESS){
				m_camera->rotateZ(-50 * delta_sec);

			}
			if (glfwGetKey(m_window, GLFW_KEY_E) == GLFW_PRESS){
				m_camera->rotateZ(50 * delta_sec);
			}

			// lookAt
			double x, y;
			glfwGetCursorPos(m_window, &x, &y);
			float rel = 10;
			float deadzone = 0.1f;
			if (!m_fpsControls) {
				rel = (float)glm::max(1.0, (sqrt(pow(m_windowWidth - (int)floor(x), 2) + pow(m_windowHeight - (int)floor(y), 2))) / m_cursorMaxDistance);
				rel = glm::max(0.0f, rel - deadzone) / (1 - deadzone);
				rel = glm::smoothstep(0.f, 1.f, rel);
			}

			float angX = ((int)floor(x) - m_windowWidth / 2) * m_angle_translate * rel;
			float angY = ((int)floor(y) - m_windowHeight / 2) * m_angle_translate * rel;

			m_camera->rotateX(angY*delta_sec);
			m_camera->rotateY(angX*delta_sec);

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
