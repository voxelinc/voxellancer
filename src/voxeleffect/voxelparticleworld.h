#pragma once

#include <list>

#include <glow/Program.h>
#include <glow/VertexArrayObject.h>
#include <glow/Buffer.h>

#include "camera.h"


class VoxelParticle;

class VoxelParticleWorld {
public:
    VoxelParticleWorld();
    ~VoxelParticleWorld();

    void addParticle(VoxelParticle* voxelParticle);

    void update(float deltaSec);
    void draw(Camera& camera);


protected:
    std::list<VoxelParticle*> m_voxelParticles;

    glow::Program m_program;
    glow::VertexArrayObject m_vertexArrayObject;

    glow::Buffer m_vertexBuffer;
    glow::Buffer m_normalBuffer;

    glow::Buffer m_positionBuffer;
    glow::Buffer m_orientationBuffer;
    glow::Buffer m_colorBuffer;
    glow::Buffer m_scaleBuffer;


    void loadProgram();
    void setupVertexAttributes();
    void setupVertexAttribute(glow::Buffer& buffer, const std::string& name, int numPerVertex, GLenum type, GLboolean normalised, int binding);
    void updateBuffers();
};

