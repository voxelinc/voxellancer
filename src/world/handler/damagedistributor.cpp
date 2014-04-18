#include "damagedistributor.h"


namespace {
enum class CellState {
    NotVisited,
    Dead,
    Survived
};
}

DamageDistributor::DamageDistributor(DamageImpact& damageImpact):
    m_damageImpact(damageImpact),
    m_damageWave(damageImpact),
    m_damage
{

}

DamageDistributor::~DamageDistributor() = 0;

void DamageDistributor::distribute() {
    while (!m_damageWave.finished()) {
        std::unordered_map<glm::ivec3, std::list<DamageFlow>> damageFlows;

        for (glm::ivec3& cell : m_damageWave.lastGeneration()) {
            for (glm::ivec3& nCell : GridNeighbourHelper(cell, false).cells()) {
                auto iter = m_damageWave.currentGeneration().find(nCell);

                if (iter != m_damageWave.currentGeneration().end()) {
                    damageFlows[cell].push_back(DamageFlow(cell, nCell));
                }
            }
        }

        for (auto pair : damageFlows) {
            Cell* cell = cellAt(pair.first);

            if (voxel != nullptr) {

            }
        }

        m_damageWave.nextGeneration();
    }
}

