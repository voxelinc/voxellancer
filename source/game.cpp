
#include "GL/glew.h"

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


#include "game.h"

Game::Game():
    m_shaderProgram(0),
    m_texture(0),
    m_vertexArrayObject(0),
    m_vertexBuffer(0),
    m_cube(0)
{
}


void Game::initialize()
{
    glow::AutoTimer t("Initialize Game");
	createAndSetupTexture();
	createAndSetupShaders();
	createAndSetupGeometry();

    m_cube = new Cube();
    
    glClearColor(0.2f, 0.3f, 0.4f, 1.f);
}

void Game::resizeEvent(
	  const unsigned int width
	, const unsigned int height)
{
	m_shaderProgram->setUniform("modelView", glm::mat4());
	m_shaderProgram->setUniform("projection", glm::ortho(0.f, 1.f, 0.f, 1.f, 0.f, 1.f));
}


void Game::update(float delta_sec)
{
    m_cube->update(delta_sec);
}

void Game::draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    glFrontFace(GL_CCW);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    
    m_cube->draw();

    m_texture->bind();
	m_shaderProgram->use();

	m_vertexArrayObject->drawArrays(GL_TRIANGLE_FAN, 0, 4);

	m_shaderProgram->release();
	m_texture->unbind();

}

void Game::createAndSetupTexture()
{
	static const int w(1024);
	static const int h(1024);
	std::unique_ptr<char[]> data(new char[w * h * 4]);

    data[0] = 'x';

    std::ifstream file("data/skybox/nebula_1024_back6.1024.1024.rgba.ub.raw", std::ios::in | std::ios::binary | std::ios::ate);
    if (file.is_open())
    {
        size_t size = file.tellg();
        assert(size == w*h * 4);
        file.seekg(0, std::ios::beg);
        file.read(data.get(), size);
        file.close();
    } else std::cout << "Unable to open file";
    
	m_texture = new glow::Texture(GL_TEXTURE_2D);

	m_texture->setParameter(GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	m_texture->setParameter(GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	m_texture->setParameter(GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	m_texture->setParameter(GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	m_texture->setParameter(GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	m_texture->image2D(0, GL_RGBA8, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, data.get());

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
		<< glm::vec3(0, 0, -0.99)
        << glm::vec3(1, 0, -0.99)
        << glm::vec3(1, 1, -0.99)
        << glm::vec3(0, 1, -0.99);

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



