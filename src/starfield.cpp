#include "starfield.h"

#include <glow/Array.h>
#include <glow/Shader.h>
#include <glow/VertexArrayObject.h>
#include <glow/VertexAttributeBinding.h>
#include <glow/Program.h>
#include <glow/Buffer.h>
#include <glowutils/File.h>
#include <glowutils/global.h>

#include "player.h"
#include "utils/randfloat.h"
#include "camera/camera.h"
#include "display/rendering/framebuffer.h"
#include "display/rendering/buffernames.h"
#include "utils/randvec.h"


static int STAR_COUNT = 1000;
static float FIELD_SIZE = 300.0f;
static float STAR_FADE_IN_SEC = 2.0f;

struct Star {
    glm::vec3 pos;
    float brightness;
    float size;
};

Starfield::Starfield(Player* player) :
    RenderPass("starfield"),
    m_player(player),
    m_time(),
    m_lastUpdate(),
    m_starfieldAge("vfx.starfieldtime"),
    m_locations()
{
    createAndSetupShaders();
    createAndSetupGeometry();
}

void Starfield::update(float deltaSec) {
    m_time += deltaSec;

    if (m_time - m_lastUpdate < 0.1) {
        return;
    }

    Star* starbuffer = (Star*) m_starBuffer->map(GL_READ_WRITE);
    glm::vec3 position = m_player->cameraPosition();

    for (int i = 0; i < STAR_COUNT; i++) {
        starbuffer[i].brightness = glm::min(1.0f, starbuffer[i].brightness + (m_time - m_lastUpdate) / STAR_FADE_IN_SEC);
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
    m_lastUpdate = m_time;

    m_starBuffer->unmap();
}

void Starfield::apply(FrameBuffer& frameBuffer, Camera& camera, EyeSide eyeside) {
    int side = eyeside == EyeSide::Left ? 0 : 1;

    addLocation(camera, side);
    cleanUp(side);

    glDisable(GL_CULL_FACE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_FALSE);

    frameBuffer.setDrawBuffers({ BufferNames::Color, BufferNames::Emissisiveness });

    glm::mat4 m1 = camera.viewProjection();
    glm::mat4 m2 = getMatrixFromPast(camera, side);

    m_shaderProgram->setUniform("viewProjection", m1);
    m_shaderProgram->setUniform("oldViewProjection", m2);
    m_shaderProgram->use();
    m_vertexArrayObject->drawArrays(GL_POINTS, 0, STAR_COUNT);

    glDepthMask(GL_TRUE);
    glDisable(GL_BLEND);
    glEnable(GL_CULL_FACE);
}

void Starfield::createAndSetupShaders() {
    glow::Shader* vertexShader = glowutils::createShaderFromFile(GL_VERTEX_SHADER, "data/shader/starfield/starfield.vert");
    glow::Shader* geometryShader = glowutils::createShaderFromFile(GL_GEOMETRY_SHADER, "data/shader/starfield/starfield.geo");
    glow::Shader* fragmentShader = glowutils::createShaderFromFile(GL_FRAGMENT_SHADER, "data/shader/starfield/starfield.frag");

    m_shaderProgram = new glow::Program();
    m_shaderProgram->attach(vertexShader, geometryShader, fragmentShader);
    m_shaderProgram->bindFragDataLocation(0, "fragColor");
}

void Starfield::createAndSetupGeometry() {
    glow::Array<Star> stars;
    for (int i = 0; i < STAR_COUNT; i++) {
        stars.push_back(Star{ RandVec3::rand(-FIELD_SIZE, FIELD_SIZE), 0.0f, RandFloat::rand(0.5f, 1.5f) });
    }

    m_starBuffer = new glow::Buffer(GL_ARRAY_BUFFER);
    m_starBuffer->setData(stars, GL_DYNAMIC_DRAW);

    m_vertexArrayObject = new glow::VertexArrayObject();
    createBinding(0, "v_vertex", offsetof(Star, pos), 3);
    createBinding(1, "v_brightness", offsetof(Star, brightness), 1);
    createBinding(2, "v_size", offsetof(Star, size), 1);
}

void Starfield::createBinding(int index, std::string name, int offset, int size) {
    glow::VertexAttributeBinding* binding = m_vertexArrayObject->binding(index);
    GLint location = m_shaderProgram->getAttributeLocation(name);
    binding->setAttribute(location);
    binding->setBuffer(m_starBuffer, 0, sizeof(Star));
    binding->setFormat(size, GL_FLOAT, GL_FALSE, offset);
    m_vertexArrayObject->enable(location);
}

void Starfield::addLocation(Camera& camera, int side) {
    CameraLocation location = CameraLocation{ m_time, camera.position(), camera.orientation() };
    m_locations[side].push_back(location);
}

glm::mat4 Starfield::getMatrixFromPast(Camera& camera, int side) {
    float past = m_time - m_starfieldAge;

    CameraLocation before = m_locations[side].back();
    CameraLocation after = m_locations[side].back();

    // find a location before 'past' and after 'past'
    auto iter = m_locations[side].rbegin();
    while (iter->time > past) {
        before = *iter;
        iter++;
        if (iter != m_locations[side].rend()) {
            after = *iter;
        } else {
            break; // not enough locations yet
        }
    }

    float interpolation = 0;
    if (before.time - after.time > 0) {
        interpolation = (past - after.time) / (before.time - after.time);
    }
    assert(interpolation >= 0 && interpolation <= 1);

    Camera c(camera);
    c.setPosition(glm::mix(after.position, before.position, interpolation));
    c.setOrientation(glm::slerp(after.orientation, before.orientation, interpolation));

    return c.viewProjection();
}

void Starfield::cleanUp(int side) {
    float past = m_time - m_starfieldAge;
    while (m_locations[side].size() > 2 && m_locations[side].at(1).time < past) {
        m_locations[side].pop_front();
    }
}

