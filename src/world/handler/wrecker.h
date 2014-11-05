#pragma once

#include <list>

class WorldObject;
class WorldObjectModification;


class Wrecker
{
public:
    void detectWreckedObjects(std::list<WorldObjectModification>& worldObjectModifications);
    std::list<WorldObject*> &wreckedObjects();
    std::list<WorldObject*> &newWreckages();

    void applyOnWreckageHooks();

protected:
    WorldObject* wreckFromObject(WorldObject* object);

    std::list<WorldObject*> m_wreckedObjects;
    std::list<WorldObject*> m_newWreckages;

};

