#include "glow\Array.h"

#include "cube.h"


Cube::Cube() : Thing()
{
    m_model_matrix = glm::translate(glm::vec3(0.8f, 0.45f, -0.5f)) * glm::scale(glm::vec3(0.4f));
    createAndSetupShaders();
    createAndSetupGeometry();

}

void Cube::update(float delta_sec)
{
    glm::vec3 c = glm::vec3(center());
    m_model_matrix = glm::translate(c) * glm::rotate(delta_sec * 90, glm::vec3(1.0f,1.0f,0.0f)) * glm::translate(-c) * m_model_matrix;

    m_shaderProgram->setUniform("modelView", m_model_matrix);
}

void Cube::draw()
{
    glEnable(GL_CULL_FACE);

    m_shaderProgram->use();
    m_vertexArrayObject->drawArrays(GL_TRIANGLES, 0, 36);
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
    m_shaderProgram->setUniform("projection", glm::ortho(0.f, 1.6f, 0.f, 0.9f, 0.1f, 1.f));
}

glow::Array<glm::vec3> strip()
{
    glm::vec3 vertices[8]
    {
        glm::vec3(-.5f,-.5f,-.5f),
        glm::vec3( .5f,-.5f,-.5f),
        glm::vec3( .5f, .5f,-.5f),
        glm::vec3(-.5f, .5f,-.5f),
        glm::vec3(-.5f,-.5f, .5f),
        glm::vec3( .5f,-.5f, .5f),
        glm::vec3( .5f, .5f, .5f),
        glm::vec3(-.5f, .5f, .5f)
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
          vertices[0], normals[4] // FRONT
        , vertices[1], normals[4]
        , vertices[2], normals[4]
        , vertices[0], normals[4]
        , vertices[2], normals[4] 
        , vertices[3], normals[4]

        , vertices[4], normals[5] // BACK
        , vertices[6], normals[5]
        , vertices[5], normals[5]
        , vertices[4], normals[5]
        , vertices[7], normals[5]
        , vertices[6], normals[5]

        , vertices[0], normals[0] // LEFT
        , vertices[3], normals[0]
        , vertices[4], normals[0]
        , vertices[3], normals[0]
        , vertices[7], normals[0]
        , vertices[4], normals[0]

        , vertices[1], normals[1] // RIGHT
        , vertices[5], normals[1]
        , vertices[6], normals[1]
        , vertices[1], normals[1]
        , vertices[6], normals[1]
        , vertices[2], normals[1]

        , vertices[3], normals[3] // TOP
        , vertices[2], normals[3]
        , vertices[6], normals[3]
        , vertices[3], normals[3]
        , vertices[6], normals[3]
        , vertices[7], normals[3]

        , vertices[0], normals[2] // BOTTOM
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
    m_vertexArrayObject->enable(0);

    auto binding1 = m_vertexArrayObject->binding(1);
    auto a_normal = m_shaderProgram->getAttributeLocation("a_normal");
    binding1->setAttribute(a_normal);
    binding1->setBuffer(m_vertexBuffer, 0, sizeof(glm::vec3) * 2);
    binding1->setFormat(3, GL_FLOAT, GL_TRUE, sizeof(glm::vec3));
    m_vertexArrayObject->enable(1);
    
}