#pragma once

#include <string>

#include "worldobject/worldobject.h"


class Jumpgate : public WorldObject {
public:
    Jumpgate();
    virtual ~Jumpgate();

    Jumpgate* buddy();
    void setBuddy(Jumpgate* buddy);


protected:
    Handle<Jumpgate> m_buddy;
};

