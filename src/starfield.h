#pragma once

#include <deque>

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

#include <glow/ref_ptr.h>

#include "property/property.h"
#include "display/rendering/renderpass.h"


namespace glow {
    class Texture;
    class Program;
    class VertexArrayObject;
    class Buffer;
};

class Player;

class Starfield : public RenderPass {
public:
    Starfield();

    virtual void update(float deltaSec, const glm::vec3& cameraPosition);
    virtual void apply(FrameBuffer& frameBuffer, const RenderMetaData& metadata) override;


private:
    struct CameraLocation {
        float time;
        glm::vec3 position;
        glm::quat orientation;
    };

    std::deque<CameraLocation> m_locations[2];
    float m_time;
    float m_lastUpdate;
    Property<float> m_starfieldAge;

    glow::ref_ptr<glow::Program> m_shaderProgram;
    glow::ref_ptr<glow::VertexArrayObject> m_vertexArrayObject;
    glow::ref_ptr<glow::Buffer> m_starBuffer;


    void createAndSetupShaders();
    void createAndSetupGeometry();

    void createBinding(int index, std::string name, int offset, int size);

    void addLocation(Camera& camera, int side);
    glm::mat4 getMatrixFromPast(Camera& camera, int side);
    void cleanUp(int side);
};
