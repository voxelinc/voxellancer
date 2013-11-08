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

#include <glow/AutoTimer.h>
#include <glow/logging.h>

#include <fmod.hpp>
#include <fmod_dsp.h>
#include <fmod_errors.h>

#include "property/propertymanager.h"

using namespace std;



Game::Game(GLFWwindow *window) :
    m_window(window),
    m_camera(),
    m_inputHandler(0),
    m_cube(0),
    m_testCluster()
{
	reloadConfig();
	m_inputHandler = new InputHandler(window, &m_camera);
    m_testCluster.moveTo(glm::vec3(-3, -3, -15));
}

Game::~Game(){
	if (m_inputHandler) delete m_inputHandler;
	if (m_cube) delete m_cube;
}

void Game::reloadConfig(){
#ifdef WIN32
	PropertyManager::getInstance()->load("data/config.ini");
#endif
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
	m_camera.setZNear(0.1f);
	m_camera.setZFar(99999);


    glClearColor(0.2f, 0.3f, 0.4f, 1.f);
	glow::debug("Game::initialize Done");
	ClusterLoader *cl = new ClusterLoader();
	cl->loadClusterFromFile("data/voxelcluster/basicship.csv", &m_testCluster);
}

void Game::update(float delta_sec)
{
	m_inputHandler->update(delta_sec);

}

void Game::draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glFrontFace(GL_CCW);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	m_skybox.draw(&m_camera);

    m_cube->prepareDraw(&m_camera);
    m_cube->draw(&m_testCluster);
    m_cube->afterDraw();

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



