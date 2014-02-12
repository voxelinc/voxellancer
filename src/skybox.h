#pragma once

#include <glow/ref_ptr.h>


namespace glow {
    class Texture;
    class Program;
    class VertexArrayObject;
    class Buffer;
}

class Camera;

class Skybox {
public:
    Skybox();

    void draw(Camera& camera);

protected:
    glow::ref_ptr<glow::Texture> m_texture;
    glow::ref_ptr<glow::Program> m_shaderProgram;
    glow::ref_ptr<glow::VertexArrayObject> m_vertexArrayObject;
    glow::ref_ptr<glow::Buffer> m_vertexBuffer;

    void initialize();

};

