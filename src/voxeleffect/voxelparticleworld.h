#pragma once

#include <memory>
#include <vector>
#include <list>

#include "glow/ref_ptr.h"
#include <glow/Program.h>
#include <glow/VertexArrayObject.h>
#include <glow/Buffer.h>

#include "camera/camera.h"
#include "etc/contextdependant.h"


class VoxelParticle;

class VoxelParticleWorld : public ContextDependant {
public:
    VoxelParticleWorld();
    ~VoxelParticleWorld();

    void addParticle(VoxelParticle* voxelParticle);

    void update(float deltaSec);
    void draw(Camera& camera);


protected:
    std::vector<VoxelParticle*> m_particles;
    std::vector<VoxelParticle*> m_tempParticles;

    int m_bufferSize;

    glow::ref_ptr<glow::Program> m_program;
    glow::ref_ptr<glow::VertexArrayObject> m_vertexArrayObject;

    glow::ref_ptr<glow::Buffer> m_particleDataBuffer;

    bool m_initialized;

    void initialize();
    void loadProgram();
    void setupVertexAttributes();
    void setupVertexAttribute(GLint offset, const std::string& name, int numPerVertex, GLenum type, GLboolean normalised, int bindingNum);
    void setBufferSize(int size);
    void updateBuffers();
    bool intersects(VoxelParticle* voxelParticle);

    virtual void beforeContextDestroy() override;
    virtual void afterContextRebuild() override;
};

