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

    bool canSpawnFail() const;

    bool canSpawn(Universe* universe) const;
    bool canSpawn(Sector* sector) const;

    void spawn(Universe* universe);
    void spawn(Sector* sector);


protected:
    Universe* m_universe;
    Sector* m_sector;
    bool m_removalScheduled;


    virtual bool doCanSpawnFail() const;
    virtual bool doCanSpawn(Universe* universe, Sector* sector) const;

    virtual void doSpawn() = 0;
};

