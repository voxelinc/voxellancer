#pragma once

#include <unordered_set>

#include "utils/component.h"

#include "equipment.h"


class WorldObject;
class WorldTreeScanner;

class Scanner : public Equipment {
public:
    Scanner(const std::string& equipmentKey, float range);
    virtual ~Scanner();

    ScannerSlot* slot();
    void setScannerSlot(ScannerSlot* slot);

    float range() const;
    void setRange(float range);

    void update(float deltaSec);

    const std::unordered_set<WorldObject*>& worldObjects();
    const std::unordered_set<WorldObject*>& foundWorldObjects();
    const std::unordered_set<WorldObject*>& lostWorldObjects();


protected:
    Component<WorldTreeScanner> m_worldTreeScanner;
    ScannerSlot* m_slot;
};

