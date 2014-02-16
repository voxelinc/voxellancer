#pragma once

#include "scripting/script.h"


class World;

class GamePlayScript: public Script {
public:
    GamePlayScript(World* world);

    virtual void load(const std::string& path) override;


protected:
    World* m_world;
};

