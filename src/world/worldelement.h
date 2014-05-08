#pragma once

#include <list>

#include <glow/Referenced.h>
#include <glow/ref_ptr.h>

#include "scripting/scriptable.h"

#include "utils/handle/handleowner.h"


class World;

class WorldElement : public glow::Referenced, public HandleOwner, public Scriptable {
public:
    WorldElement();
    virtual ~WorldElement();

    World* world();
    void setWorld(World* world);

    virtual void update(float deltaSec);


protected:
    World* m_world;
};

