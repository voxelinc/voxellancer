
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

#include "game.h"
#include "ddstexture.h"
#include "ddstexturecube.h"

const float Game::s_angle_translate = 0.001f;
const float Game::s_move_translate = 0.01f;

Game::Game():
    m_shaderProgram(0),
    m_texture(0),
    m_vertexArrayObject(0),
    m_vertexBuffer(0),
    m_cube(0),
	m_cam(0)
{

}


void Game::initialize()
{
    glow::AutoTimer t("Initialize Game");
	createAndSetupTexture();
	createAndSetupShaders();
	createAndSetupGeometry();
    
    //testFMOD();

    m_cube = new Cube();
	m_cam = new glow::Camera();
	m_cam->setViewport(glm::ivec2(16, 9));
	m_cam->setCenter(glm::vec3(0, 0, 1));
	m_cam->setUp(glm::vec3(0, 1, 0));
	m_cam->setEye(glm::vec3(0, 0, 0));
	m_cam->setZNear(0.1f);
	m_cam->setZFar(999999);
	angX = glm::radians(90.0f);
	angY = 0;
	SetCursorPos(100, 100);

    glClearColor(0.2f, 0.3f, 0.4f, 1.f);
}

void Game::resizeEvent(
	  const unsigned int width
	, const unsigned int height)
{
	m_shaderProgram->setUniform("modelView", glm::mat4());
	m_shaderProgram->setUniform("projection", glm::mat4()); // glm::ortho(0.f, 1.f, 0.f, 1.f, 0.f, 1.f));
}


void Game::update(float delta_sec)
{
    //m_cube->update(delta_sec);
	glm::vec3 lookVec = m_cam->center() - m_cam->eye();

	// position "eye"
	if (GetKeyState(*"W") & 0x80){
		m_cam->setEye(m_cam->eye() + lookVec*s_move_translate);
	} 
	if (GetKeyState(*"A") & 0x80){
		m_cam->setEye(m_cam->eye() - glm::cross(lookVec, m_cam->up())*s_move_translate);
	} 
	if (GetKeyState(*"S") & 0x80){
		m_cam->setEye(m_cam->eye() - lookVec*s_move_translate);
	} 
	if (GetKeyState(*"D") & 0x80){
		m_cam->setEye(m_cam->eye() + glm::cross(lookVec, m_cam->up())*s_move_translate);
	}

	// lookAt
	POINT cp;
	GetCursorPos(&cp);
	angX += (cp.x - 100)*s_angle_translate;
	angY += (cp.y - 100)*s_angle_translate; 
	if (angY > glm::radians(90.0f)) angY = glm::radians(90.0f);
	else if (angY < glm::radians(-90.0f)) angY = glm::radians(-90.0f);
	m_cam->setCenter(m_cam->eye() + glm::normalize(glm::vec3(glm::cos(angX),glm::sin(-angY),glm::sin(angX))));
	SetCursorPos(100, 100);
}

void Game::draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glDisable(GL_DEPTH_TEST);
	glFrontFace(GL_CCW);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	m_texture->bind();
	glm::vec3 camEye = m_cam->eye();
	glm::vec3 camCenter = m_cam->center();
	m_cam->setEye(glm::vec3(0, 0, 0));
	m_cam->setCenter(camCenter - camEye);
	m_shaderProgram->setUniform("projection_actual", m_cam->viewInverted());
	m_shaderProgram->setUniform("projection", m_cam->projection());
	//m_shaderProgram->setUniform("projection_actual", glm::rotate(glm::degrees(angX), glm::vec3(0, 1, 0))*glm::rotate(glm::degrees(-angY), glm::vec3(0,0,1)));
	m_shaderProgram->use();

	m_vertexArrayObject->drawArrays(GL_TRIANGLE_FAN, 0, 4);

	m_cam->setEye(camEye);
	m_cam->setCenter(camCenter);
	m_shaderProgram->release();
	m_texture->unbind();

	glEnable(GL_DEPTH_TEST);
	m_cube->drawtest(m_cam->viewProjection());
	//m_cube->draw();


}

void Game::createAndSetupTexture()
{
	m_texture = DdsTextureCube::load("data/skybox/nebula_1024_right1.dds",
		"data/skybox/nebula_1024_left2.dds",
		"data/skybox/nebula_1024_top3.dds",
		"data/skybox/nebula_1024_bottom4.dds",
		"data/skybox/nebula_1024_front5.dds",
		"data/skybox/nebula_1024_back6.dds");
    m_texture->setParameter(GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	m_texture->setParameter(GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	m_texture->setParameter(GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	m_texture->setParameter(GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	m_texture->setParameter(GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);


}

void Game::createAndSetupShaders()
{
	glow::Shader * vertexShader = glow::Shader::fromFile(GL_VERTEX_SHADER, "data/test.vert");
	glow::Shader * fragmentShader = glow::Shader::fromFile(GL_FRAGMENT_SHADER, "data/test.frag");

	m_shaderProgram = new glow::Program();
	m_shaderProgram->attach(vertexShader, fragmentShader);
	m_shaderProgram->bindFragDataLocation(0, "fragColor");

	m_shaderProgram->getUniform<GLint>("texture")->set(0);
}

void Game::createAndSetupGeometry()
{
	auto vertices = glow::Array<glm::vec3>()
		<< glm::vec3(-1, -1, -1)
        << glm::vec3(1, -1, -1)
        << glm::vec3(1, 1, -1)
        << glm::vec3(-1, 1, -1);

	m_vertexArrayObject = new glow::VertexArrayObject();

	m_vertexBuffer = new glow::Buffer(GL_ARRAY_BUFFER);
	m_vertexBuffer->setData(vertices);

	auto binding1 = m_vertexArrayObject->binding(0);
	auto a_vertex = m_shaderProgram->getAttributeLocation("a_vertex");

	binding1->setAttribute(a_vertex);
	binding1->setBuffer(m_vertexBuffer, 0, sizeof(glm::vec3));
	binding1->setFormat(3, GL_FLOAT, GL_FALSE, 0);

	m_vertexArrayObject->enable(a_vertex);
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



