#include "genericworldobject.h"

#include "resource/clustercache.h"

#include "worldobject/components/hardpoint.h"
#include "worldobject/components/engineslot.h"


GenericWorldObject::GenericWorldObject(const std::string& propertyPrefix):
    GenericEntity(propertyPrefix)
{
    Property<float> scale(propertyPrefix + ".general.scale", 1.0f);
    m_transform.setScale(scale);

    std::string clusterFile = Property<std::string>(propertyPrefix + ".general.voxelcluster");
    ClusterCache::instance()->fillObject(this, std::string("data/voxelcluster/") + clusterFile);

    setupHardpoints(propertyPrefix);
    setupEngineSlots(propertyPrefix);
}

void GenericWorldObject::setupHardpoints(const std::string& propertyPrefix) {
    for(Hardpoint* hardpoint : components().hardpoints()) {
        std::string prefix = propertyPrefix + ".hardpoint" + std::to_string(hardpoint->index()) + ".";

        hardpoint->setDirection(Property<glm::vec3>(prefix + "direction"));
        hardpoint->setFieldOfAim(Property<glm::vec2>(prefix + "fieldOfAim"));

        std::list<std::string> mountableWeapons = Property<std::list<std::string>>(prefix + "mountable");
        for(std::string& weapon : mountableWeapons) {
            hardpoint->setMountable(weapon, true);
        }
    }
}

void GenericWorldObject::setupEngineSlots(const std::string& propertyPrefix) {
    for(EngineSlot* engineSlot : components().engineSlots()) {
        std::string prefix = propertyPrefix + ".engineslot" + std::to_string(engineSlot->index()) + ".";

        engineSlot->setDirection(Property<glm::vec3>(prefix + "direction"));

        std::list<std::string> mountableEngines = Property<std::list<std::string>>(prefix + "mountable");
        for(std::string& engine : mountableEngines) {
            engineSlot->setMountable(engine, true);
        }
    }
}
