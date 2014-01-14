#pragma once

#include <glow/ref_ptr.h>
#include <glow/Array.h>

#include <glm/glm.hpp>


namespace glow {
    class Program;
    class VertexArrayObject;
    class Buffer;
};


class VoxelMesh {
public:
    static void bindTo(glow::ref_ptr<glow::Program> program, 
                       glow::ref_ptr<glow::VertexArrayObject> vao, 
                       int index = 0);
    static void tearDown();
protected:
    static glow::ref_ptr<glow::Buffer> vertexBuffer();
    static void initBuffer();

    static glow::ref_ptr<glow::Buffer> s_vertexBuffer;

};

