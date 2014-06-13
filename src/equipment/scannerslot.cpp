#include "scannerslot.h"


ScannerSlot::ScannerSlot(WorldObjectComponents* components, int index):
    WorldObjectSlot(components, index)
{

}

ScannerSlot::~ScannerSlot() = default;

std::shared_ptr<Scanner>& ScannerSlot::scanner() {
    return m_scanner;
}

void ScannerSlot::setScanner(const std::shared_ptr<Scanner>& scanner) {
    m_scanner = scanner;
}

void ScannerSlot::update(float deltaSec) {
    if (m_scanner) {
        m_scanner->update(deltaSec);
    }
}


