#pragma once

#include <memory>
#include <list>

#include "glow/ref_ptr.h"
#include <glow/Program.h>
#include <glow/VertexArrayObject.h>
#include <glow/Buffer.h>

#include "camera.h"


class VoxelParticle;
struct ParticleData;

class VoxelParticleWorld {
public:
    VoxelParticleWorld();
    ~VoxelParticleWorld();

    void addParticle(VoxelParticle* voxelParticle);

    void update(float deltaSec);
    void draw(Camera& camera);


protected:
    std::list<VoxelParticle*> m_voxelParticles;

    glow::ref_ptr<glow::Program> m_program;
    glow::ref_ptr<glow::VertexArrayObject> m_vertexArrayObject;

    glow::ref_ptr<glow::Buffer> m_particleBuffer;


    bool m_initialized;
    int m_bufferSize;

    void initialize();
    void loadProgram();
    void setupVertexAttributes();
    void setupVertexAttribute(size_t offset, const std::string& name, int numPerVertex, GLenum type, GLboolean normalised, int binding);
    void setBufferSize(int size);
    void updateBuffers();
    bool intersects(VoxelParticle* voxelParticle);
};
