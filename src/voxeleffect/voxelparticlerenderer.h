#pragma once

#include <string>

#include "etc/contextdependant.h"
#include "property/property.h"

#include "voxelparticledata.h"
#include "voxelmesh.h"


namespace glow {
    class Buffer;
    class Program;
    class VertexArrayObject;
}

class Camera;
class VoxelParticleEngine;

/*
    Component of a VoxelParticleEngine responsible for rendering the particles
    It holds its own GPU-Buffer and receives updates for the particles by updateBuffer()
*/
class VoxelParticleRenderer :  public ContextDependant {
public:
    VoxelParticleRenderer(VoxelParticleEngine* engine);

    void updateBuffer(int begin, int end, VoxelParticleData* data);

    void draw(const Camera& camera);


protected:
    VoxelMesh m_voxelMesh;

    bool m_initialized;
    VoxelParticleEngine* m_engine;
    int m_bufferSize;

    Property<glm::vec3> m_defaultLightDir;

    glow::ref_ptr<glow::Buffer> m_gpuParticleBuffer;
    glow::ref_ptr<glow::Program> m_program;
    glow::ref_ptr<glow::VertexArrayObject> m_vertexArrayObject;


    void initialize();
    void loadProgram();
    void setupVertexAttributes();
    void setupVertexAttribute(GLint offset, const std::string& name, int numPerVertex, GLenum type, GLboolean normalised, int bindingNum);
    void setupVertexAttribDivisors();
    void setBufferSize(int bufferSize);

    virtual void beforeContextDestroy() override;
    virtual void afterContextRebuild() override;
};

