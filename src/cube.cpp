#include <glow/Array.h>
#include <glow/Shader.h>
#include <glow/VertexAttributeBinding.h>

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include "cube.h"

#include "glow/Array.h"
#include "glow/VertexAttributeBinding.h"


Cube::Cube() :
m_texture(0),
m_shaderProgram(0),
m_vertexArrayObject(0),
m_vertexBuffer(0)
{
	m_model_matrix = glm::translate(glm::vec3(0.0, 0.0, 0.0f)) * glm::scale(glm::vec3(0.08f));
	createAndSetupShaders();
	createAndSetupGeometry();

}

const glm::vec4 Cube::center()
{
	return m_model_matrix * glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
}

void Cube::update(float delta_sec)
{
    glm::vec3 c = glm::vec3(center());
    m_model_matrix = glm::translate(c) * glm::rotate(delta_sec * 90, glm::vec3(0.0f,1.0f,1.0f)) * glm::translate(-c) * m_model_matrix;

    m_shaderProgram->setUniform("modelView", m_model_matrix);
}

void Cube::draw()
{
	m_shaderProgram->use();
	m_vertexArrayObject->drawArraysInstanced(GL_TRIANGLES, 0, 36, 1000);
	m_shaderProgram->release();

}

void Cube::drawtest(glm::mat4 projection)
{
	m_shaderProgram->setUniform("projection", projection);
	m_shaderProgram->use();
	m_vertexArrayObject->drawArraysInstanced(GL_TRIANGLES, 0, 36, 1000);
	m_shaderProgram->release();

}


void Cube::createAndSetupShaders()
{
    glow::Shader * vertexShader = glow::Shader::fromFile(GL_VERTEX_SHADER, "data/cube.vert");
    glow::Shader * fragmentShader = glow::Shader::fromFile(GL_FRAGMENT_SHADER, "data/cube.frag");

    m_shaderProgram = new glow::Program();
    m_shaderProgram->attach(vertexShader, fragmentShader);
    m_shaderProgram->bindFragDataLocation(0, "fragColor");

    m_shaderProgram->setUniform("modelView", m_model_matrix);
    m_shaderProgram->setUniform("projection", glm::perspective(60.f, 16.f/9.f, 0.1f, 1000.0f)); // move to camera
}

glow::Array<glm::vec3> strip()
{
    glm::vec3 vertices[8]
    {
        glm::vec3(-.5f,-.5f, .5f),
        glm::vec3( .5f,-.5f, .5f),
        glm::vec3( .5f, .5f, .5f),
        glm::vec3(-.5f, .5f, .5f),
        glm::vec3(-.5f,-.5f,-.5f),
        glm::vec3( .5f,-.5f,-.5f),
        glm::vec3( .5f, .5f,-.5f),
        glm::vec3(-.5f, .5f,-.5f)
    };

    glm::vec3 normals[6]
    {
        glm::vec3(-1, 0, 0),
        glm::vec3(1, 0, 0),
        glm::vec3(0, -1, 0),
        glm::vec3(0, 1, 0),
        glm::vec3(0, 0, -1),
        glm::vec3(0, 0, 1),
    };

    // use an interleaved array
    return glow::Array<glm::vec3>
    {
          vertices[0], normals[5] //front
        , vertices[1], normals[5]
        , vertices[2], normals[5]
        , vertices[0], normals[5]
        , vertices[2], normals[5]
        , vertices[3], normals[5]

        , vertices[4], normals[4] //back
        , vertices[6], normals[4]
        , vertices[5], normals[4]
        , vertices[4], normals[4]
        , vertices[7], normals[4]
        , vertices[6], normals[4]

        , vertices[0], normals[0] //left
        , vertices[3], normals[0]
        , vertices[4], normals[0]
        , vertices[3], normals[0]
        , vertices[7], normals[0]
        , vertices[4], normals[0]

        , vertices[1], normals[1] //right
        , vertices[5], normals[1]
        , vertices[6], normals[1]
        , vertices[1], normals[1]
        , vertices[6], normals[1]
        , vertices[2], normals[1]

        , vertices[3], normals[3] //top
        , vertices[2], normals[3]
        , vertices[6], normals[3]
        , vertices[3], normals[3]
        , vertices[6], normals[3]
        , vertices[7], normals[3]

        , vertices[0], normals[2] //bottom
        , vertices[5], normals[2]
        , vertices[1], normals[2]
        , vertices[0], normals[2]
        , vertices[4], normals[2]
        , vertices[5], normals[2]
    };
}

void Cube::createAndSetupGeometry()
{
    m_vertexArrayObject = new glow::VertexArrayObject();

    m_vertexBuffer = new glow::Buffer(GL_ARRAY_BUFFER);
    m_vertexBuffer->setData(strip());

    auto binding0 = m_vertexArrayObject->binding(0);
    auto a_vertex = m_shaderProgram->getAttributeLocation("a_vertex");

    binding0->setAttribute(a_vertex);
    binding0->setBuffer(m_vertexBuffer, 0, sizeof(glm::vec3) * 2);
    binding0->setFormat(3, GL_FLOAT, GL_FALSE, 0);
    m_vertexArrayObject->enable(a_vertex);

    auto binding1 = m_vertexArrayObject->binding(1);
    auto a_normal = m_shaderProgram->getAttributeLocation("a_normal");
    binding1->setAttribute(a_normal);
    binding1->setBuffer(m_vertexBuffer, 0, sizeof(glm::vec3) * 2);
    binding1->setFormat(3, GL_FLOAT, GL_TRUE, sizeof(glm::vec3));
    m_vertexArrayObject->enable(a_normal);

}
