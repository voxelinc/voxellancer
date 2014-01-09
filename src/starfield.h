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

class Starfield {
public:
    Starfield();

    void draw(Camera* m_camera);

private:
    void createAndSetupShaders();
    void createAndSetupGeometry();

    glm::vec3 m_oldPos;

    glow::ref_ptr<glow::Program> m_shaderProgram;
    glow::ref_ptr<glow::VertexArrayObject> m_vertexArrayObject;
    glow::ref_ptr<glow::Buffer> m_starBuffer;
};