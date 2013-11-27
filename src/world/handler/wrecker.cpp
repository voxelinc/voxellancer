#include "wrecker.h"

void Wrecker::detectWreckages(std::list<WorldObject*> &modifiedVoxelClusters) {
    m_wreckages.clear();
}

std::list<WorldObject*> &Wrecker::wreckages() {
    return m_wreckages;
}


std::list<WorldObject*> &Wrecker::recycled() {
    return m_recycled;
}
