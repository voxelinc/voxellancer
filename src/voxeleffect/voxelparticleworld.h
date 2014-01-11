#pragma once

#include <memory>
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

    glow::ref_ptr<glow::Program> m_program;
    glow::ref_ptr<glow::VertexArrayObject> m_vertexArrayObject;

    std::unique_ptr<glow::Buffer> m_positionBuffer;
    std::unique_ptr<glow::Buffer> m_orientationBuffer;
    std::unique_ptr<glow::Buffer> m_colorBuffer;
    std::unique_ptr<glow::Buffer> m_scaleBuffer;

    bool m_initialized;


    void initialize();
    void loadProgram();
    void setupVertexAttributes();
    void setupVertexAttribute(std::unique_ptr<glow::Buffer>& buffer, const std::string& name, int numPerVertex, GLenum type, GLboolean normalised, int binding);
    void updateBuffers();
    bool intersects(VoxelParticle* voxelParticle);
};

