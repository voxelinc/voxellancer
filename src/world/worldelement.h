#pragma once

#include <glow/Referenced.h>

#include "scripting/scriptable.h"

#include "utils/handle/handleowner.h"


class World;

/**
 * Base class for all Objects that make up a running World
 * Offers glow::Referenced capabilities and a reference to the World
 * it exists in.
 * A WorldElement can either be an active in the World which means that it is
 * update()d and influences the World. In that case activeInWorld() returns true.
 * When created a activeInWorld() is false by default and activateInWorld() needs to be called
 * before the WorldElement can take active part in the World
 * When a WorldElement is no longer needed or shouldn't influence the World further,
 * call deactivateInWorld(). When no glow::ref_ptr<> point to the WorldElement anymore it will be
 * deleted automatically.
 */
class WorldElement : public glow::Referenced, public HandleOwner, public Scriptable {
public:
    WorldElement(World* world);
    virtual ~WorldElement();

    World* world();

    bool activeInWorld() const;

    void activateInWorld();
    void deactivateInWorld();

    virtual void update(float deltaSec);


protected:
    virtual void onActivationInWorld();
    virtual void onDeactivationInWorld();


protected:
    World* m_world;


private:
    bool m_active;
};

