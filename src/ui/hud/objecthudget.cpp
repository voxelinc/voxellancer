#include "objecthudget.h"

#include <cmath>

#include <glm/glm.hpp>

#include "ai/character.h"

#include "factions/factionrelation.h"
#include "factions/factionmatrix.h"
#include "factions/playerfaction.h"

#include "utils/geometryhelper.h"

#include "world/world.h"

#include "worldobject/worldobject.h"
#include "worldobject/ship.h"

#include "player.h"

#include "hudobjectdelegate.h"
#include "hud.h"
#include "voxel/voxelclusterbounds.h"
#include "objecthudgetvoxels.h"


ObjectHudget::ObjectHudget(HUD* hud, HUDObjectDelegate* objectDelegate):
    Hudget(hud),
    m_objectDelegate(objectDelegate),
    m_voxels(new ObjectHudgetVoxels(this))
{

}

ObjectHudget::~ObjectHudget() = default;

void ObjectHudget::update(float deltaSec) {
    bool targetHighlight = false;
    FactionRelationType relationType = FactionRelationType::Neutral;
    WorldObject* worldObject = m_objectDelegate->worldObject();

    if(worldObject) {
        calculateOpeningAngle();
        pointToWorldPoint(worldObject->transform().position());

        if(m_hud->player()->ship()) {
            if(worldObject == m_hud->player()->ship()->targetObject()) {
                targetHighlight = true;
            }
            // TODO: Replace the following two lines with proper WorldObjectType mechanism
            Ship* ship = dynamic_cast<Ship*>(worldObject);
            if (ship) {
                Faction* faction = ship->character()->faction();

                if (faction) {
                    relationType = faction->relationTo(World::instance()->factionMatrix().playerFaction())->type();
                }
            }
        }
    }

    m_voxels->setTargetHightlight(targetHighlight);
    m_voxels->setRelationType(relationType);
    m_voxels->update(deltaSec);
}

void ObjectHudget::draw() {
    m_voxels->draw();
}

void ObjectHudget::calculateOpeningAngle() {
    WorldObject* worldObject = m_objectDelegate->worldObject();

    float radius = worldObject->bounds().sphere().radius();
    float distance = glm::length(m_hud->centerOfView() - worldObject->transform().position());
    float alpha = std::atan2(radius, distance) * 0.95f;

    alpha = std::max(alpha, 0.04f); // Hack, set minimum size

    m_voxels->setOpeningAngle(alpha);
}

