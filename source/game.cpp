
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

#include <iostream>

using namespace std;


const float Game::s_angle_translate = 0.1f;
const float Game::s_move_translate = 0.5f;

Game::Game(GLFWwindow *window):
	m_window(window),
    m_shaderProgram(0),
    m_texture(0),
    m_vertexArrayObject(0),
    m_vertexBuffer(0),
    m_cube(0),
	m_cam(0),
    m_player()
{

}


void Game::initialize()
{
    glow::AutoTimer t("Initialize Game");
    cout << "createAndSetupTexture()" << endl;
	createAndSetupTexture();
    cout << "createAndSetupShaders()" << endl;
	createAndSetupShaders();
    cout << "createAndSetupGeometry()" << endl;
	createAndSetupGeometry();
    
    cout << "test FMOD()" << endl;
    testFMOD();

    cout << "Create cube" << endl;
    m_cube = new Cube();

	cout << "Create cam" << endl;
	m_cam = new glow::Camera();
	//viewport set in resize
	m_cam->setCenter(glm::vec3(0, 0, 1));
	m_cam->setUp(glm::vec3(0, 1, 0));
	m_cam->setEye(glm::vec3(0, 0, 0));
	m_cam->setZNear(0.1f);
	m_cam->setZFar(99999);

	glfwGetWindowSize(m_window, &windowWidth, &windowHeight);
	glfwSetCursorPos(m_window, windowWidth / 2, windowHeight / 2);
	cursorMaxDistance = min(windowHeight, windowWidth);

	fpsControls = true;
	glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

    glClearColor(0.2f, 0.3f, 0.4f, 1.f);
    cout << "Done" << endl;
}

void Game::resizeEvent(
	  const unsigned int width
	, const unsigned int height)
{
	glfwGetWindowSize(m_window, &windowWidth, &windowHeight);
	m_cam->setViewport(glm::ivec2(windowWidth, windowHeight));
}


void Game::update(float delta_sec)
{
	m_cube->update(delta_sec);

	if (glfwGetWindowAttrib(m_window, GLFW_FOCUSED)){

		glm::vec3 lookVec = m_cam->center() - m_cam->eye();
		// position "eye"
		if (glfwGetKey(m_window, GLFW_KEY_W) == GLFW_PRESS){
            m_player.move(glm::vec3(0, 0, s_move_translate* delta_sec));
		} 
		if (glfwGetKey(m_window, GLFW_KEY_A) == GLFW_PRESS){
            m_player.move(glm::vec3(s_move_translate * delta_sec, 0, 0));

        }
        if (glfwGetKey(m_window, GLFW_KEY_S) == GLFW_PRESS){
            m_player.move(glm::vec3(0, 0, -s_move_translate* delta_sec));

        }
        if (glfwGetKey(m_window, GLFW_KEY_D) == GLFW_PRESS){
            m_player.move(glm::vec3(-s_move_translate* delta_sec, 0, 0));
        }
        if (glfwGetKey(m_window, GLFW_KEY_Q) == GLFW_PRESS){
            m_player.rotateZ(-50*delta_sec);

        }
        if (glfwGetKey(m_window, GLFW_KEY_E) == GLFW_PRESS){
            m_player.rotateZ(50 * delta_sec);
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
	
        m_player.rotateX(angY*delta_sec);
        m_player.rotateY(angX*delta_sec);

    }
}

void Game::draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glFrontFace(GL_CCW);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

    glDisable(GL_DEPTH_TEST);

    m_texture->bind();
	m_shaderProgram->setUniform("viewInverted", glm::inverse(glm::mat4_cast(m_player.orientation())));
	m_shaderProgram->setUniform("projection", m_cam->projection());
	m_shaderProgram->use();

	m_vertexArrayObject->drawArrays(GL_TRIANGLE_FAN, 0, 4);

	m_shaderProgram->release();
	m_texture->unbind();

    glEnable(GL_DEPTH_TEST);

    m_cube->drawtest(m_cam->projection() * m_player.matrix());
    
	m_shaderProgram->use();
	m_vertexArrayObject->drawArrays(GL_POINTS, 0, 1);
	m_shaderProgram->release();

}

void Game::createAndSetupTexture()
{
	m_texture = new glow::Texture(GL_TEXTURE_CUBE_MAP);
	DdsTexture::loadImageCube(m_texture,
	"data/skybox/nebula_1024_right1.dds",
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



