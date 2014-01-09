#pragma once

#include <glm/glm.hpp>

#include <glow/ref_ptr.h>


namespace glow {
    class Texture;
    class Program;
    class VertexArrayObject;
    class Buffer;
};

class Camera;
class Player;

class Starfield {
public:
    Starfield(Player* player, Camera* camera);

    void draw();
    void update(float deltaSec);

private:
    void createAndSetupShaders();
    void createAndSetupGeometry();

    Camera* m_camera;
    Player* m_player;

    float m_nextupdate;

    glow::ref_ptr<glow::Program> m_shaderProgram;
    glow::ref_ptr<glow::VertexArrayObject> m_vertexArrayObject;
    glow::ref_ptr<glow::Buffer> m_starBuffer;
};