#pragma once

#include <list>

#include <glow/Referenced.h>
#include <glow/ref_ptr.h>

#include "scripting/scriptable.h"

#include "utils/handle/handleowner.h"


class Sector;
class Universe;

class GameObject : public glow::Referenced, public HandleOwner, public Scriptable {
public:
    GameObject();
    virtual ~GameObject();

    Universe* universe() const;
    Sector* sector() const;

    bool removalScheduled() const;
    void scheduleRemoval();

    virtual void update(float deltaSecs);

    bool spawn(Universe* universe);
    bool spawn(Sector* sector);


protected:
    Universe* m_universe;
    Sector* m_sector;
    bool m_removalScheduled;

    virtual bool doSpawn() = 0;
};

