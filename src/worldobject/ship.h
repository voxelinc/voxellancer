#pragma once

#include <list>
#include <memory>

#include "worldobject.h"
#include "property/property.h"



class World;
class God;
class Hardpoint;
class Engine;
class Character;
class Sound;
class FormationLogic;
class BoardComputer;

class Ship: virtual public WorldObject {
public:
    Ship();
    virtual ~Ship();

    virtual void update(float deltaSec) override;

    Handle<Ship> shipHandle();

    void setTargetObject(WorldObject* target);
    WorldObject* targetObject();

    BoardComputer* boardComputer();
    FormationLogic* formationLogic();

    void setCharacter(Character* character);
    Character* character();

//    void setEngineSound(std::shared_ptr<Sound> sound);



protected:
    Ship(CollisionFilter* collisionFilter);

    std::unique_ptr<Character> m_character;
    std::unique_ptr<BoardComputer> m_boardComputer;
    std::unique_ptr<FormationLogic> m_formationLogic;
//    std::shared_ptr<Sound> m_sound;
//    glm::vec3 m_enginePos;

    Handle<Ship> m_shipHandle;
    Handle<WorldObject> m_targetObjectHandle;

    void updateEnginePosition();
};

