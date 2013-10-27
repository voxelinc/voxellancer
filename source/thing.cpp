#include "thing.h"

Thing::Thing():
    m_shaderProgram(0),
    m_vertexArrayObject(0),
    m_vertexBuffer(0),
    m_model_matrix(1.0)
{

}


const glm::vec4 Thing::center()
{
    return m_model_matrix * glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
}

const glm::vec4 Thing::up()
{
    return glm::normalize(m_model_matrix * glm::vec4(0.0f, 1.0f, 0.0f, 0.0f));
}

const glm::vec4 Thing::direction()
{
    return glm::normalize(m_model_matrix * glm::vec4(0.0f, 0.0f, 1.0f, 0.0f));
}


void Thing::update(float delta_sec)
{

}

