#pragma once

#include "worldobjectslot.h"


class ScannerSlot : public WorldObjectSlot {
public:
    ScannerSlot(WorldObjectComponents* components, int index);
    virtual ~ScannerSlot();

    std::shared_ptr<Scanner>& scanner();
    void setScanner(const std::shared_ptr<Scanner>& scanner);

    void update(float deltaSec);


protected:
    std::shared_ptr<Scanner> m_scanner;
};

