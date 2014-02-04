#pragma once

#include <string>

#include "utils/genericentity.h"

#include "worldobject.h"


class GenericWorldObject: virtual public WorldObject, public GenericEntity {
public:
    GenericWorldObject(const std::string& propertyPrefix);


protected:
    void setupHardpoints(const std::string& propertyPrefix);
    void setupEngineSlots(const std::string& propertyPrefix);
};

