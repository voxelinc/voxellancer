#pragma once

#include <unordered_set>
#include <unordered_map>
#include <string>

#include "geometry/sphere.h"

#include "utils/component.h"

#include "worldobject/worldobject.h"


class Line;
class WorldObject;
class WorldTreeScanner;

class Jumpgate : public WorldObject {
public:
    Jumpgate();
    virtual ~Jumpgate();

    Jumpgate* buddy();
    void setBuddy(Jumpgate* buddy);

    virtual void update(float deltaSec) override;


protected:
    Handle<Jumpgate> m_buddy;
    Component<WorldTreeScanner> m_scanner;

    std::unordered_map<WorldObject*, glm::vec3> m_lastPositions;

    bool crossesWarpzone(const Line& line);
    void transfer(WorldObject* object);
};

