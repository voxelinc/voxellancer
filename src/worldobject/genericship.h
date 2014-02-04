#pragma once

#include <string>

#include "ship.h"
#include "genericworldobject.h"


class GenericShip: public Ship, public GenericWorldObject {
public:
    GenericShip(const std::string& propertyPrefix);
};

