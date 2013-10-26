
#include "GL/glew.h"

#include <algorithm>
#include <random>

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
#include <glow/logging.h>


#include "game.h"

void Game::initialization()
{
	createAndSetupTexture();
	createAndSetupShaders();
	createAndSetupGeometry();
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

}

void Game::draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	m_texture->bind();
	m_shaderProgram->use();

	m_vertexArrayObject->drawArrays(GL_TRIANGLE_FAN, 0, 4);

	m_shaderProgram->release();
	m_texture->unbind();
}

void Game::createAndSetupTexture()
{
	static const int w(256);
	static const int h(256);
	unsigned char data[w * h * 4];

	std::random_device rd;
	std::mt19937 generator(rd());

	std::poisson_distribution<> r(0.2);

	for (int i = 0; i < w * h * 4; ++i)
		data[i] = 255 - static_cast<unsigned char>(r(generator) * 255);

	m_texture = new glow::Texture(GL_TEXTURE_2D);

	m_texture->setParameter(GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	m_texture->setParameter(GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	m_texture->setParameter(GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	m_texture->setParameter(GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	m_texture->setParameter(GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	m_texture->image2D(0, GL_RGBA8, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
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
		<< glm::vec3(0, 0, 0)
		<< glm::vec3(1, 0, 0)
		<< glm::vec3(1, 1, 0)
		<< glm::vec3(0, 1, 0);

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



