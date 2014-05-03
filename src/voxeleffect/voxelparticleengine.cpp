#include "voxelparticleengine.h"

#include "voxelparticledata.h"
#include "voxelparticlerenderer.h"
#include "voxelparticlesetup.h"

#include "particlechecks/voxelparticleremover.h"
#include "particlechecks/voxelparticleremovecheck.h"
#include "particlechecks/voxelparticleintersectioncheck.h"
#include "particlechecks/voxelparticleexpirecheck.h"
#include "particlechecks/voxelparticlefuturecheck.h"

#include "world/world.h"


VoxelParticleEngine::VoxelParticleEngine():
    m_time(0.0f),
    m_initialized(false),
    m_renderer(new VoxelParticleRenderer(this)),
    m_remover(new VoxelParticleRemover(this)),
    m_gpuParticleBufferInvalid(false),
    m_gpuParticleBufferInvalidBegin(0),
    m_gpuParticleBufferInvalidEnd(0)
{
    m_remover->addCheck(std::make_shared<VoxelParticleExpireCheck>(*this));
    m_remover->addCheck(std::make_shared<VoxelParticleIntersectionCheck>(*this));
    setBufferSize(1024);
}

VoxelParticleEngine::~VoxelParticleEngine() = default;

float VoxelParticleEngine::time() const {
    return m_time;
}

int VoxelParticleEngine::particleDataCount() const {
    return m_cpuParticleBuffer.size();
}

int VoxelParticleEngine::particleCount() const {
    return m_cpuParticleBuffer.size() - m_freeParticleBufferIndices.size();
}

VoxelParticleData* VoxelParticleEngine::particleData(int index) {
    return &m_cpuParticleBuffer[index];
}

std::vector<VoxelParticleData>& VoxelParticleEngine::particleDataVector() {
    return m_cpuParticleBuffer;
}

void VoxelParticleEngine::setPlayer(Player& m_player) {
    m_remover->setPlayer(m_player);
}

void VoxelParticleEngine::addParticle(const VoxelParticleSetup& particleSetup, const VoxelCluster* creator) {
    VoxelParticleData particle = particleSetup.toData(m_time);

    if (creator != nullptr && VoxelParticleFutureCheck::intersectsIn(particle, 0.1f, *creator)) {
        return;
    }

    if(m_freeParticleBufferIndices.empty()) {
        setBufferSize(m_cpuParticleBuffer.size() * 2);
    }

    int bufferIndex = m_freeParticleBufferIndices.top();
    m_cpuParticleBuffer[bufferIndex] = particle;
    particleChanged(bufferIndex);

    m_freeParticleBufferIndices.pop();
}

void VoxelParticleEngine::removeParticle(int index) {
    assert(index < m_cpuParticleBuffer.size());

    VoxelParticleData& particle = m_cpuParticleBuffer[index];
    particle.status = VoxelParticleData::Status::Removed;
    m_freeParticleBufferIndices.push(index);
    //particle.color = 0xff00ff;

    particleChanged(index);
}

void VoxelParticleEngine::update(float deltaSec) {
    m_time += deltaSec;
    m_remover->update(deltaSec);
}

void VoxelParticleEngine::draw(const Camera& camera) {
    if (m_gpuParticleBufferInvalid) {
        updateGPUBuffers(m_gpuParticleBufferInvalidBegin, m_gpuParticleBufferInvalidEnd);
    }

    m_renderer->draw(camera);
}

void VoxelParticleEngine::particleChanged(int bufferIndex) {
    int oldInvalidBegin = m_gpuParticleBufferInvalidBegin;
    int oldInvalidEnd = m_gpuParticleBufferInvalidEnd;

    if (m_gpuParticleBufferInvalid) {
        if(bufferIndex < m_gpuParticleBufferInvalidBegin) {
            m_gpuParticleBufferInvalidBegin = bufferIndex;
        } else if (bufferIndex > m_gpuParticleBufferInvalidEnd) {
            m_gpuParticleBufferInvalidEnd = bufferIndex;
        }
    } else {
        m_gpuParticleBufferInvalid = true;
        m_gpuParticleBufferInvalidBegin = bufferIndex;
        m_gpuParticleBufferInvalidEnd = bufferIndex;
    }
    /*
     * If the range of particles gets too big, probably because of too many
     * particles between two free positions, push the old range to the gpu
     */
    int oldInvalidCount = oldInvalidEnd - oldInvalidBegin;
    int newInvalidCount = m_gpuParticleBufferInvalidEnd - m_gpuParticleBufferInvalidBegin;
    if (newInvalidCount - oldInvalidCount > 512) {
        updateGPUBuffers(oldInvalidBegin, oldInvalidEnd);
        m_gpuParticleBufferInvalidBegin = bufferIndex;
        m_gpuParticleBufferInvalidEnd = bufferIndex;
    }
}

void VoxelParticleEngine::setBufferSize(int bufferSize) {
    for(int i = m_cpuParticleBuffer.size(); i < bufferSize; i++) {
        m_freeParticleBufferIndices.push(i);
    }

    m_cpuParticleBuffer.resize(bufferSize);

    // Rather be safe than sorry for now
    m_gpuParticleBufferInvalid = true;
    m_gpuParticleBufferInvalidBegin = 0;
    m_gpuParticleBufferInvalidEnd = bufferSize - 1;
}


/*
 * Update the GPU buffers of all components that use such
 */
void VoxelParticleEngine::updateGPUBuffers(int begin, int end) {
    m_renderer->updateBuffer(begin, end, &m_cpuParticleBuffer[begin]);

    m_gpuParticleBufferInvalid = false;
}

void VoxelParticleEngine::beforeContextDestroy() {
    // nothing to do
}

void VoxelParticleEngine::afterContextRebuild() {
    updateGPUBuffers(0, m_cpuParticleBuffer.size()-1);
}

