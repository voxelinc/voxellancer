#pragma once

#include <list>

#include <glow/Referenced.h>
#include <glow/ref_ptr.h>

#include "scripting/scriptable.h"

#include "utils/handle/handleowner.h"


class Sector;
class Universe;

class UniverseElement : public glow::Referenced, public HandleOwner, public Scriptable {
public:
    UniverseElement();
    virtual ~UniverseElement();

    Universe* universe();
    void setUniverse(Universe* universe);

    Sector* sector();
    void setSector(Sector* sector);

    bool removalScheduled() const;
    void scheduleRemoval();

    virtual void update(float deltaSecs);

    virtual void spawn() = 0;


protected:
    Universe* m_universe;
    Sector* m_sector;
    bool m_removalScheduled;
};

