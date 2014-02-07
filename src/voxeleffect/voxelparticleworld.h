#pragma once

#include <memory>
#include <vector>
#include <stack>
#include <list>

#include "glow/ref_ptr.h"
#include <glow/Program.h>
#include <glow/VertexArrayObject.h>
#include <glow/Buffer.h>

#include "camera/camera.h"

#include "property/property.h"

#include "voxelparticledata.h"
#include "voxelparticlesetup.h"



class VoxelParticleWorld {
public:
    VoxelParticleWorld();

    void addParticle(const VoxelParticleSetup& particleSetup);

    void update(float deltaSec);
    void draw(Camera& camera);


protected:
    float m_time;

    std::vector<VoxelParticleData> m_cpuParticleBuffer;
    glow::ref_ptr<glow::Buffer> m_gpuParticleBuffer;

    std::stack<int> m_freeParticleBufferIndices;

    glow::ref_ptr<glow::Program> m_program;
    glow::ref_ptr<glow::VertexArrayObject> m_vertexArrayObject;

    Property<float> m_fullDeadCheckInterval;
    int m_deadCheckIndex;

    Property<float> m_fullIntersectionCheckInterval;
    int m_intersectionCheckIndex;

    bool m_initialized;

    bool m_gpuParticleBufferInvalid;
    int m_gpuParticleBufferInvalidBegin;
    int m_gpuParticleBufferInvalidEnd;


    void initialize();
    void loadProgram();
    void setupVertexAttributes();
    void setupVertexAttribute(GLint offset, const std::string& name, int numPerVertex, GLenum type, GLboolean normalised, int bindingNum);
    void setupVertexAttribDivisors();

    void setBufferSize(int bufferSize);
    void setParticleAt(const VoxelParticleData& particle, int bufferIndex);
    void updateGPUBuffer();

    void performDeadChecks(float deltaSec);
    void performIntersectionChecks(float deltaSec);

    bool intersects(VoxelParticleData* particle);
};

