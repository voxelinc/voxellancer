#include "scanner.h"

#include "worldtree/worldtreescanner.h"


Scanner::Scanner(const std::string& equipmentKey, float range):
    m_slot(nullptr)
{
    m_worldTreeScanner->setScanRadius(range);
}

Scanner::~Scanner() = default;

ScannerSlot* Scanner::slot() {
    return m_slot;
}

void Scanner::setScannerSlot(ScannerSlot* slot) {
    m_slot = slot;
}

float Scanner::range() const {
    return m_worldTreeScanner->scanRadius();
}

void Scanner::setRange(float range) {
    m_worldTreeScanner->setScanRadius(range);
}

void Scanner::update(float deltaSec) {
    if (m_slot) {
        m_worldTreeScanner->update(deltaSec, m_slot->components()->worldObject());
    }
}

const std::unordered_set<WorldObject*>& Scanner::worldObjects() {
    return m_worldTreeScanner->worldObjects();
}

const std::unordered_set<WorldObject*>& Scanner::foundWorldObjects() {
    return m_worldTreeScanner->foundWorldObjects();
}

const std::unordered_set<WorldObject*>& Scanner::lostWorldObjects() {
    return m_worldTreeScanner->lostWorldObjects();
}


