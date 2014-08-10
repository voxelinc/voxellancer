#include "starfield.h"

#include <glow/Shader.h>
#include <glow/VertexArrayObject.h>
#include <glow/VertexAttributeBinding.h>
#include <glow/Program.h>
#include <glow/Buffer.h>
#include <glowutils/File.h>
#include <glowutils/global.h>

#include "player.h"
#include "utils/randfloat.h"
#include "display/rendering/framebuffer.h"
#include "display/rendering/buffernames.h"
#include "utils/randvec3.h"
#include "etc/contextdependant.h"
#include "camera/camera.h"


const static float STAR_FADE_IN_SEC = 0.5f;


Starfield::Starfield() :
    RenderPass("starfield"),
    m_time(),
    m_starfieldAge("starfield.time"),
    m_starSize("starfield.size"),
    m_starCount("starfield.count"),
    m_fieldRadius("starfield.radius"),
    m_locations(),
    m_cpuBuffer()
{
    createAndSetupShaders();
    createAndSetupGeometry();
}

void Starfield::update(float deltaSec, const glm::vec3& cameraPosition) {
    m_time += deltaSec;

    glm::vec3 position = cameraPosition;

    if (m_starCount != m_cpuBuffer.size() || m_fieldRadius != m_oldFieldRadius) {
        glow::debug("starfield rebuild");
        createAndSetupGeometry(); // property changed
    }

    for (int i = 0; i < m_cpuBuffer.size(); i++) {
        m_cpuBuffer[i].brightness = glm::min(1.0f, m_cpuBuffer[i].brightness + deltaSec / STAR_FADE_IN_SEC);
        while (m_cpuBuffer[i].pos.x - position.x < -m_fieldRadius) {
            m_cpuBuffer[i].pos.x += 2 * m_fieldRadius;
            m_cpuBuffer[i].brightness = 0;
        }
        while (m_cpuBuffer[i].pos.x - position.x > m_fieldRadius) {
            m_cpuBuffer[i].pos.x -= 2 * m_fieldRadius;
            m_cpuBuffer[i].brightness = 0;
        }
        while (m_cpuBuffer[i].pos.y - position.y < -m_fieldRadius) {
            m_cpuBuffer[i].pos.y += 2 * m_fieldRadius;
            m_cpuBuffer[i].brightness = 0;
        }
        while (m_cpuBuffer[i].pos.y - position.y > m_fieldRadius) {
            m_cpuBuffer[i].pos.y -= 2 * m_fieldRadius;
            m_cpuBuffer[i].brightness = 0;
        }
        while (m_cpuBuffer[i].pos.z - position.z < -m_fieldRadius) {
            m_cpuBuffer[i].pos.z += 2 * m_fieldRadius;
            m_cpuBuffer[i].brightness = 0;
        }
        while (m_cpuBuffer[i].pos.z - position.z > m_fieldRadius) {
            m_cpuBuffer[i].pos.z -= 2 * m_fieldRadius;
            m_cpuBuffer[i].brightness = 0;
        }
    }

    m_gpuBuffer->setData(m_cpuBuffer, GL_STREAM_DRAW);
}

void Starfield::apply(FrameBuffer& frameBuffer, const RenderMetaData& metadata) {
    if (m_starCount == 0) {
        return;
    }
    int side = (metadata.eyeside() == EyeSide::Right);

    addLocation(metadata.camera(), side);
    cleanUp(side);

    glDisable(GL_CULL_FACE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_FALSE);

    frameBuffer.setDrawBuffers({ BufferNames::Color, BufferNames::Emissisiveness });

    glm::mat4 m1 = metadata.camera().viewProjection();
    glm::mat4 m2 = getMatrixFromPast(metadata.camera(), side);

    m_shaderProgram->setUniform("viewProjection", m1);
    m_shaderProgram->setUniform("oldViewProjection", m2);
    m_shaderProgram->setUniform("sizeFactor", m_starSize.get());
    m_shaderProgram->use();
    m_vertexArrayObject->drawArrays(GL_POINTS, 0, m_starCount);

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
    m_cpuBuffer.clear();
    for (int i = 0; i < m_starCount; i++) {
        m_cpuBuffer.push_back(StarData{ RandVec3::rand(-m_fieldRadius, m_fieldRadius), 0.0f, RandFloat::rand(0.5f, 1.5f) });
    }

    m_oldFieldRadius = m_fieldRadius;

    m_gpuBuffer = new glow::Buffer(GL_ARRAY_BUFFER);
    m_gpuBuffer->setData(m_cpuBuffer, GL_STREAM_DRAW);

    m_vertexArrayObject = new glow::VertexArrayObject();
    createBinding(0, "v_vertex", offsetof(StarData, pos), 3);
    createBinding(1, "v_brightness", offsetof(StarData, brightness), 1);
    createBinding(2, "v_size", offsetof(StarData, size), 1);
}

void Starfield::createBinding(int index, std::string name, int offset, int size) {
    glow::VertexAttributeBinding* binding = m_vertexArrayObject->binding(index);
    GLint location = m_shaderProgram->getAttributeLocation(name);
    binding->setAttribute(location);
    binding->setBuffer(m_gpuBuffer, 0, sizeof(StarData));
    binding->setFormat(size, GL_FLOAT, GL_FALSE, offset);
    m_vertexArrayObject->enable(location);
}

void Starfield::addLocation(const Camera& camera, int side) {
    CameraLocation location = CameraLocation{ m_time, camera.eye(), camera.orientation() };
    m_locations[side].push_back(location);
}

glm::mat4 Starfield::getMatrixFromPast(const Camera& camera, int side) {
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
    c.setEye(glm::mix(after.position, before.position, interpolation));
    c.setOrientation(glm::slerp(after.orientation, before.orientation, interpolation));

    return c.viewProjection();
}

void Starfield::cleanUp(int side) {
    float past = m_time - m_starfieldAge;
    while (m_locations[side].size() > 2 && m_locations[side].at(1).time < past) {
        m_locations[side].pop_front();
    }
}

void Starfield::beforeContextDestroy() {
    m_vertexArrayObject = nullptr;
    m_gpuBuffer = nullptr;
    m_shaderProgram = nullptr;
}

void Starfield::afterContextRebuild() {
    createAndSetupShaders();
    createAndSetupGeometry();
}

