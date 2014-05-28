#include "universe.h"

#include <algorithm>
#include <iostream>

#include "factions/factionmatrix.h"

#include "scripting/scriptengine.h"

#include "player.h"

#include "gameobjectmanager.h"
#include "sector.h"


Universe::Universe():
    m_player(*this),
    m_functionalObjects(*this)
{

}

Universe::~Universe() = default;

Player& Universe::player() {
    return m_player;
}

ScriptEngine& Universe::scriptEngine() {
    return m_scriptEngine;
}

FactionMatrix& Universe::factionMatrix() {
    return m_factionMatrix;
}

void Universe::addSector(const std::shared_ptr<Sector>& sector) {
    m_sectors.push_back(sector);
}

Sector* Universe::sector(const std::string& name) {
    auto iter = std::find_if(m_sectors.begin(), m_sectors.end(), [&] (const std::shared_ptr<Sector>& sector) {
        return sector->name() == name;
    });

    return iter == m_sectors.end() ? nullptr : iter->get();
}

void Universe::addFunctionalObject(FunctionalObject* object) { std::cout << "Add functional: " << object << std::endl;
    m_functionalObjects->addObject(object);
}

void Universe::removeFunctionalObject(FunctionalObject* object) { std::cout << "Remove functional: " << object << std::endl;
    m_functionalObjects->removeObject(object);
}

void Universe::update(float deltaSec) {
    m_functionalObjects->update(deltaSec);

    m_player->update(deltaSec);
    m_scriptEngine->update(deltaSec);

    for (std::shared_ptr<Sector>& sector : m_sectors) {
        sector->update(deltaSec);
    }
}

