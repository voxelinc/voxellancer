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



static int STAR_COUNT = 1000;
static float FIELD_SIZE = 200.0f;

// to be replaced by helper!
glm::vec3 randVec(float from, float to) {
    return glm::vec3(
        RandFloat::rand(from, to),
        RandFloat::rand(from, to),
        RandFloat::rand(from, to)
        );
}

struct Star {
    glm::vec3 pos;
    float brightness;
    float size;
};

Starfield::Starfield(Player* player, Camera* camera):
    m_camera(camera),
    m_player(player)
{
    createAndSetupShaders();
    createAndSetupGeometry();
}

void Starfield::update(float deltaSec) {

    Star* starbuffer = (Star*) m_starBuffer->map(GL_READ_WRITE);
    glm::vec3 position = m_player->playerShip()->transform().position();

    // only perform once per second if this is a performance problem
    for (int i = 0; i < STAR_COUNT; i++) {
        starbuffer[i].brightness = glm::min(1.0f, starbuffer[i].brightness + deltaSec * 0.5f);
        while (starbuffer[i].pos.x - position.x < -FIELD_SIZE) {
            starbuffer[i].pos.x += 2 * FIELD_SIZE;
            starbuffer[i].brightness = 0;
        }
        while (starbuffer[i].pos.x - position.x > FIELD_SIZE) {
            starbuffer[i].pos.x -= 2 * FIELD_SIZE;
            starbuffer[i].brightness = 0;
        }
        while (starbuffer[i].pos.y - position.y < -FIELD_SIZE) {
            starbuffer[i].pos.y += 2 * FIELD_SIZE;
            starbuffer[i].brightness = 0;
        }
        while (starbuffer[i].pos.y - position.y > FIELD_SIZE) {
            starbuffer[i].pos.y -= 2 * FIELD_SIZE;
            starbuffer[i].brightness = 0;
        }
        while (starbuffer[i].pos.z - position.z < -FIELD_SIZE) {
            starbuffer[i].pos.z += 2 * FIELD_SIZE;
            starbuffer[i].brightness = 0;
        }
        while (starbuffer[i].pos.z - position.z > FIELD_SIZE) {
            starbuffer[i].pos.z -= 2 * FIELD_SIZE;
            starbuffer[i].brightness = 0;
        }
    }

    m_starBuffer->unmap();
}


void Starfield::draw() {
    glDisable(GL_CULL_FACE);
    glEnable(GL_BLEND); 
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    m_shaderProgram->setUniform("viewProjection", m_camera->viewProjection());
    m_shaderProgram->setUniform("speed", glm::vec4(m_player->playerShip()->physics().speed(), 0));
    m_shaderProgram->setUniform("aspectRatio", m_camera->aspectRatio());
    m_shaderProgram->use();
    m_vertexArrayObject->drawArrays(GL_POINTS, (GLint)0, (GLsizei)STAR_COUNT);
    
    glDisable(GL_BLEND);
    glEnable(GL_CULL_FACE);
}

void Starfield::createAndSetupShaders() {
    glow::Shader * vertexShader = glowutils::createShaderFromFile(GL_VERTEX_SHADER, "data/starfield/starfield.vert");
    glow::Shader * geometryShader = glowutils::createShaderFromFile(GL_GEOMETRY_SHADER, "data/starfield/starfield.geo");
    glow::Shader * fragmentShader = glowutils::createShaderFromFile(GL_FRAGMENT_SHADER, "data/starfield/starfield.frag");

    m_shaderProgram = new glow::Program();
    m_shaderProgram->attach(vertexShader, geometryShader, fragmentShader);
    m_shaderProgram->bindFragDataLocation(0, "fragColor");


}


void Starfield::createAndSetupGeometry() {
    m_vertexArrayObject = new glow::VertexArrayObject();

    m_starBuffer = new glow::Buffer(GL_ARRAY_BUFFER);

    glow::Array<Star> stars;

    for (int i = 0; i < STAR_COUNT; i++) {
        stars.push_back(Star{ randVec(-FIELD_SIZE, FIELD_SIZE), 0.0f, RandFloat::rand(0.5f, 1.5f)});
    }
    m_starBuffer->setData(stars);

    auto binding0 = m_vertexArrayObject->binding(0);
    auto a_vertex0 = m_shaderProgram->getAttributeLocation("a_vertex");
    binding0->setAttribute(a_vertex0);
    binding0->setBuffer(m_starBuffer, 0, sizeof(Star));
    binding0->setFormat(3, GL_FLOAT, GL_FALSE, 0);
    m_vertexArrayObject->enable(a_vertex0);

    auto binding1 = m_vertexArrayObject->binding(1);
    auto a_vertex1 = m_shaderProgram->getAttributeLocation("a_brightness");
    binding1->setAttribute(a_vertex1);
    binding1->setBuffer(m_starBuffer, 0, sizeof(Star));
    binding1->setFormat(1, GL_FLOAT, GL_FALSE, offsetof(Star, Star::brightness));
    m_vertexArrayObject->enable(a_vertex1);

    auto binding2 = m_vertexArrayObject->binding(2);
    auto a_vertex2 = m_shaderProgram->getAttributeLocation("a_size");
    binding2->setAttribute(a_vertex2);
    binding2->setBuffer(m_starBuffer, 0, sizeof(Star));
    binding2->setFormat(1, GL_FLOAT, GL_FALSE, offsetof(Star, Star::size));
    m_vertexArrayObject->enable(a_vertex2);

}