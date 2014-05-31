#pragma once

#include <list>

#include <glow/Referenced.h>
#include <glow/ref_ptr.h>

#include "scripting/scriptable.h"

#include "utils/handle/handleowner.h"


class Sector;
class Universe;

enum class GameObjectState {
    Created,
    Spawned,
    Unspawned
};

class GameObject : public glow::Referenced, public HandleOwner, public Scriptable {
public:
    GameObject();
    virtual ~GameObject();

    Universe* universe() const;
    Sector* sector() const;

    GameObjectState gameObjectState() const;

    virtual void update(float deltaSecs);

    bool canSpawn(Universe& universe) const;
    bool canSpawn(Sector& sector) const;

    void spawn(Universe& universe);
    void spawn(Sector& sector);

    void unspawn();

    void warp(Sector& sector);


protected:
    Universe* m_universe;
    Sector* m_sector;
    GameObjectState m_state;


    virtual bool doCanSpawn(Universe& universe, Sector* sector) const;
    virtual void doSpawn() = 0;

    virtual void doUnspawn() = 0;

    virtual void doWarp(Sector& sector) = 0;
};

