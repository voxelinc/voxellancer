#pragma once

#include <string>



#include "voxelparticledata.h"

#include "voxelmesh.h"


namespace glow {
    class Buffer;
    class Program;
    class VertexArrayObject;
}

class Camera;
class VoxelParticleEngine;

class VoxelParticleRenderer {
public:
    VoxelParticleRenderer(VoxelParticleEngine* engine);

    void updateBuffer(int begin, int end, VoxelParticleData* data);

    void draw(Camera& camera);


protected:
    VoxelMesh m_voxelMesh;

    bool m_initialized;
    VoxelParticleEngine* m_engine;
    int m_bufferSize;

    glow::ref_ptr<glow::Buffer> m_gpuParticleBuffer;
    glow::ref_ptr<glow::Program> m_program;
    glow::ref_ptr<glow::VertexArrayObject> m_vertexArrayObject;


    void initialize();
    void loadProgram();
    void setupVertexAttributes();
    void setupVertexAttribute(GLint offset, const std::string& name, int numPerVertex, GLenum type, GLboolean normalised, int bindingNum);
    void setupVertexAttribDivisors();
    void setBufferSize(int bufferSize);
};

