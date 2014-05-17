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

    Universe* universe();
    Sector* sector();

    bool removalScheduled() const;
    void scheduleRemoval();

    virtual void update(float deltaSecs);

    void spawn(Universe* universe);
    void spawn(Sector* sector);


protected:
    Universe* m_universe;
    Sector* m_sector;
    bool m_removalScheduled;

    virtual void doSpawn() = 0;
};

