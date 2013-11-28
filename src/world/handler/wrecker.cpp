#include "wrecker.h"
#include "worldobject.h"


void Wrecker::detectWreckages(std::set<WorldObject*> &modifiedVoxelClusters) {
    m_wreckages.clear();
}

std::list<WorldObject*> &Wrecker::wreckages() {
    return m_wreckages;
}


std::list<WorldObject*> &Wrecker::recycled() {
    return m_recycled;
}
