#pragma once

#include <unordered_set>
#include <string>

#include "geometry/sphere.h"

#include "worldobject/worldobject.h"


class Jumpgate : public WorldObject {
public:
    Jumpgate();
    virtual ~Jumpgate();

    Jumpgate* buddy();
    void setBuddy(Jumpgate* buddy);

    virtual void update(float deltaSec) override;


protected:
    Handle<Jumpgate> m_buddy;
    Sphere m_sphere;

    std::unordered_set<WorldObject*> scan();
    void transfer(WorldObject* object);
};

