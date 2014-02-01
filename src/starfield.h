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

class Camera;
class Player;

class Starfield : public RenderPass {
public:
    Starfield(Player* player);

    virtual void update(float deltaSec) override;
    virtual void apply(FrameBuffer& frameBuffer, Camera& camera, EyeSide side) override;

private:
    struct CameraLocation {
        float time;
        glm::vec3 position;
        glm::quat orientation;
    };

    void createAndSetupShaders();
    void createAndSetupGeometry();

    void addLocation(Camera& camera, int side);
    glm::mat4 getMatrixFromPast(Camera& camera, int side);
    void cleanUp(int side);

    Player* m_player;
    std::deque<CameraLocation> m_locations;
    float m_time;
    Property<float> m_starfieldAge;

    glow::ref_ptr<glow::Program> m_shaderProgram;
    glow::ref_ptr<glow::VertexArrayObject> m_vertexArrayObject;
    glow::ref_ptr<glow::Buffer> m_starBuffer;
};