#include "game.h"

#include <GL/glew.h>

#include <algorithm>
#include <random>
#include <memory>
#include <iostream>
#include <fstream>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

#include <glow/Error.h>
#include <glow/Uniform.h>
#include <glow/Array.h>
#include <glow/ShaderFile.h>
#include <glow/Program.h>
#include <glow/VertexArrayObject.h>
#include <glow/AutoTimer.h>
#include <glow/logging.h>

#include <fmod.hpp>
#include <fmod_dsp.h>
#include <fmod_errors.h>

#include "ddstexture.h"

using namespace std;


const float Game::s_angle_translate = 0.1f;
const float Game::s_move_translate = 0.5f;

Game::Game(GLFWwindow *window):
	m_window(window),
    m_cube(0),
	m_camera()
{

}


void Game::initialize()
{
    glow::AutoTimer t("Initialize Game");
    
	glow::debug("Game::testFMOD()");
    testFMOD();

	glow::debug("Create Cube");
    m_cube = new Cube();

	glow::debug("Setup Camera");
	//viewport set in resize
	m_camera.moveTo(glm::vec3(0, 0, 1));
	m_camera.rotateTo(glm::angleAxis(180.0f, glm::vec3(0, 1, 0)));
	m_camera.setZNear(0.1f);
	m_camera.setZFar(99999);

	glfwGetWindowSize(m_window, &windowWidth, &windowHeight);
	glfwSetCursorPos(m_window, windowWidth / 2, windowHeight / 2);
	cursorMaxDistance = min(windowHeight, windowWidth);

	fpsControls = true;
	glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

    glClearColor(0.2f, 0.3f, 0.4f, 1.f);
	glow::debug("Game::initialize Done");
}

void Game::resizeEvent(
	  const unsigned int width
	, const unsigned int height)
{
	glfwGetWindowSize(m_window, &windowWidth, &windowHeight);
	m_camera.setViewport(glm::ivec2(windowWidth, windowHeight));
}


void Game::update(float delta_sec)
{
	m_cube->update(delta_sec);

	if (glfwGetWindowAttrib(m_window, GLFW_FOCUSED)){

		// position "eye"
		if (glfwGetKey(m_window, GLFW_KEY_W) == GLFW_PRESS){
			m_camera.move(glm::vec3(0, 0, s_move_translate* delta_sec));
		} 
		if (glfwGetKey(m_window, GLFW_KEY_A) == GLFW_PRESS){
            m_camera.move(glm::vec3(s_move_translate * delta_sec, 0, 0));

        }
        if (glfwGetKey(m_window, GLFW_KEY_S) == GLFW_PRESS){
            m_camera.move(glm::vec3(0, 0, -s_move_translate* delta_sec));

        }
        if (glfwGetKey(m_window, GLFW_KEY_D) == GLFW_PRESS){
            m_camera.move(glm::vec3(-s_move_translate* delta_sec, 0, 0));
        }
        if (glfwGetKey(m_window, GLFW_KEY_Q) == GLFW_PRESS){
            m_camera.rotateZ(-50*delta_sec);

        }
        if (glfwGetKey(m_window, GLFW_KEY_E) == GLFW_PRESS){
            m_camera.rotateZ(50 * delta_sec);
        }

		// lookAt
		double x, y;
		glfwGetCursorPos(m_window, &x, &y);
		float rel = 10;
        float deadzone = 0.1f;
		if (!fpsControls) {
			rel = (float)max(1.0,(sqrt(pow(windowWidth - (int)floor(x), 2) + pow(windowHeight - (int)floor(y), 2))) / cursorMaxDistance);
            rel = max(0.0f, rel - deadzone) / (1-deadzone);
            rel = glm::smoothstep(0.f,1.f,rel);
        }
		else
		{
			glfwSetCursorPos(m_window, windowWidth / 2, windowHeight / 2);
		}

		float angX = ((int)floor(x) - windowWidth/2) * s_angle_translate * rel;
		float angY = ((int)floor(y) - windowHeight/2) * s_angle_translate * rel;
	
        m_camera.rotateX(angY*delta_sec);
        m_camera.rotateY(angX*delta_sec);

    }
}

void Game::draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glFrontFace(GL_CCW);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	m_skybox.draw(&m_camera);

    m_cube->drawtest(m_camera.projection() * m_camera.view());
   
	/* Added as hd7000 fix
	* @xchrdw: why? where to put?
	m_shaderProgram->use();
	m_vertexArrayObject->drawArrays(GL_POINTS, 0, 1);
	m_shaderProgram->release();
	*/

}

void ERRCHECK(FMOD_RESULT result)
{
    if (result != FMOD_OK)
    {
        printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
        exit(-1);
    }
}

void Game::testFMOD()
{
    FMOD::System * system = 0;
    FMOD::Sound  * sound = 0;
    FMOD::Channel *channel = 0;

    FMOD_RESULT result = FMOD::System_Create(&system);
    ERRCHECK(result);

    result = system->init(32, FMOD_INIT_NORMAL, 0);
    ERRCHECK(result);

    result = system->createSound("data/LASER.mp3", FMOD_SOFTWARE, 0, &sound);
    ERRCHECK(result);

    result = system->playSound(FMOD_CHANNEL_FREE, sound, false, &channel);
    ERRCHECK(result);
}

void Game::toggleControls()
{
	if (fpsControls)
	{
		fpsControls = !fpsControls;
		glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	}
	else
	{
		fpsControls = !fpsControls;
		glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
	}
}



