#pragma once

#include <list>

#include "world/helper/worldobjectmodification.h"


class BoundsShrinker {
public:
    void shrink(std::list<WorldObjectModification>& worldObjectModifications);
};
