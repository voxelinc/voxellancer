#include "starfield.h"

#include <glow/Array.h>
#include <glow/Shader.h>
#include <glow/Texture.h>
#include <glow/VertexArrayObject.h>
#include <glow/VertexAttributeBinding.h>
#include <glow/Program.h>
#include <glow/Buffer.h>
#include <glow/Shader.h>
#include <glowutils/File.h>

#include "camera.h"
#include "player.h"

#include "utils/randfloat.h"



static int MAX_STARS = 10000;

// to be replaced by helper!
glm::vec3 randVec(float from, float to) {
    return glm::vec3(
        RandFloat::rand(from, to),
        RandFloat::rand(from, to),
        RandFloat::rand(from, to)
        );
}

Starfield::Starfield(Player* player, Camera* camera):
    m_camera(camera),
    m_player(player)
{
    createAndSetupShaders();
    createAndSetupGeometry();
}

void Starfield::update(float deltaSec) {

}


void Starfield::draw() {
    m_shaderProgram->setUniform("viewProjection", m_camera->viewProjection());
    m_shaderProgram->setUniform("speed", glm::vec4(m_player->playerShip()->physics().speed(), 0));

    m_vertexArrayObject->drawArrays(GL_POINTS, (GLint)0, (GLsizei)MAX_STARS);

}

void Starfield::createAndSetupShaders() {
    glow::Shader * vertexShader = glowutils::createShaderFromFile(GL_VERTEX_SHADER, "data/starfield/starfield.vert");
    glow::Shader * geometryShader = glowutils::createShaderFromFile(GL_GEOMETRY_SHADER, "data/starfield/starfield.geo");
    glow::Shader * fragmentShader = glowutils::createShaderFromFile(GL_FRAGMENT_SHADER, "data/starfield/starfield.frag");

    m_shaderProgram = new glow::Program();
    m_shaderProgram->attach(vertexShader, geometryShader, fragmentShader);
    m_shaderProgram->bindFragDataLocation(0, "fragColor");

    //m_shaderProgram->getUniform<GLint>("positionSampler")->set(0);

}


void Starfield::createAndSetupGeometry() {
    m_vertexArrayObject = new glow::VertexArrayObject();

    m_starBuffer = new glow::Buffer(GL_ARRAY_BUFFER);

    glow::Array<glm::vec3> stars;

    for (int i = 0; i < MAX_STARS; i++) {
        stars.push_back(randVec(-1000, 1000));
    }

    m_starBuffer->setData(stars);

    auto binding0 = m_vertexArrayObject->binding(0);
    auto a_vertex = m_shaderProgram->getAttributeLocation("a_vertex");

    binding0->setAttribute(a_vertex);
    binding0->setBuffer(m_starBuffer, 0, sizeof(glm::vec3));
    binding0->setFormat(3, GL_FLOAT, GL_FALSE, 0);
    m_vertexArrayObject->enable(a_vertex);

}