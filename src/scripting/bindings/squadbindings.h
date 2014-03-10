#pragma once

#include "bindings.h"

class SquadBindings : public Bindings {
public:
    SquadBindings(GamePlayScript& script);

protected:
    virtual void initialize();

};
