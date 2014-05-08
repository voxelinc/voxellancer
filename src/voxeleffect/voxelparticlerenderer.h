#pragma once

#include <string>

#include <GL/glew.h>

#include "etc/contextdependant.h"
#include "property/property.h"

#include "voxelparticledata.h"


namespace glow {
    class Buffer;
    class Program;
    class VertexArrayObject;
}

class Camera;
class VoxelMesh;
class VoxelParticleEngineImpl;

/**
 * Component of a VoxelParticleEngineImpl responsible for rendering the particles
 * It holds its own GPU-Buffer and receives updates for the particles by updateBuffer()
 */
class VoxelParticleRenderer :  public ContextDependant {
public:
    VoxelParticleRenderer(VoxelParticleEngineImpl* engine);
    ~VoxelParticleRenderer();

    void updateBuffer(int begin, int end, VoxelParticleData* data);

    void draw(const Camera& camera, bool transparentPass);


protected:
    std::unique_ptr<VoxelMesh> m_voxelMesh;

    bool m_initialized;
    VoxelParticleEngineImpl* m_engine;
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

