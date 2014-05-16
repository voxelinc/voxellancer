#pragma once

#include <list>

class WorldObject;
class WorldObjectModification;


class Wrecker
{
public:
    void wreck(std::list<WorldObjectModification>& worldObjectModifications);

protected:
    void createWreckFromObject(WorldObject* object);
};

