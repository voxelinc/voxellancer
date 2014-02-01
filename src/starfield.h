#pragma once

#include <queue>

#include <glm/glm.hpp>

#include <glow/ref_ptr.h>

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
    void createAndSetupShaders();
    void createAndSetupGeometry();
    
    Player* m_player;
    std::queue<glm::mat4> m_matricesQueue[2];

    glow::ref_ptr<glow::Program> m_shaderProgram;
    glow::ref_ptr<glow::VertexArrayObject> m_vertexArrayObject;
    glow::ref_ptr<glow::Buffer> m_starBuffer;
};