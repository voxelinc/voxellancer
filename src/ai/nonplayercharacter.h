#pragma once

#include <memory>

#include "character.h"

/**
 * A NPC is a character that can execute an AiTask on
 * its own
 */
class NonPlayerCharacter : public Character {
public:
    NonPlayerCharacter();
    virtual ~NonPlayerCharacter();

    virtual void update(float deltaSec) override;
};

