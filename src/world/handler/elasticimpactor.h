#pragma once

#include <list>

#include "world/helper/impact.h"


class ElasticImpactor {
public:
    void parse(std::list<Impact>& worldObjectImpacts);
};
