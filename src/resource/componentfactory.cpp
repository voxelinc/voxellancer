#include "ComponentFactory.h"

ComponentFactory::ComponentFactory() {
    PropertyManager::instance()->load("data/components/enginemk1.ini", "enginemk1");
    PropertyManager::instance()->load("data/components/gun.ini", "gun");
    PropertyManager::instance()->load("data/components/piratethruster.ini", "piratethruster");
    PropertyManager::instance()->load("data/components/rocketlauncher.ini", "rocketlauncher");
    PropertyManager::instance()->load("data/components/snowcanon.ini", "snowcanon");
}

Weapon* ComponentFactory::weapon(const std::string& name) {
    if (name == "gun") {

    }
    if (name == "rocketlauncher") {

    }
    if (name == "snowcanon") {

    }
}

Engine* ComponentFactory::engine(const std::string& name) {
    if (name == "piratethruster") {

    }
    if (name == "enginemk1") {

    }
}

