#pragma once

#include <list>

#include <glow/Referenced.h>
#include <glow/ref_ptr.h>

#include "scripting/scriptable.h"

#include "utils/handle/handleowner.h"


class World;

class WorldElement : public glow::Referenced, public HandleOwner, public Scriptable {
public:
    explicit WorldElement(World* world);
    explicit WorldElement(WorldElement* parent);
    virtual ~WorldElement();

    World* world();
    void setWorld(World* world);

    virtual bool isAddableToWorld(World* world) const;

    virtual void onAddToWorld();
    virtual void onRemovalFromWorld();

    virtual void registerInWorldComponents();
    virtual void deregisterInWorldComponents();

    std::list<WorldElement*> children() const;

    void addChild(WorldElement* child);
    void removeChild(WorldElement* child);

    virtual void update(float deltaSec);


protected:
    World* m_world;
    WorldElement* m_parent;
    std::list<glow::ref_ptr<WorldElement>> m_children;
};

