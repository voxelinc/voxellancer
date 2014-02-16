#include "gameplayscript.h"

GamePlayScript::GamePlayScript(World* world):
    Script(),
    m_world(world)
{

}

void GamePlayScript::load(const std::string& path) {
    Script::load(path);

    // Bind functions
}
