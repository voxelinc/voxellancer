#pragma once

#include "geometry/abstractmove.h"

/**
 * Values from -1 to +1 on each directional and
 * angular axis represent the relative power of an engine
 * that is to be used
 *
 * E.g. direction() = (0.5, -0.8, -1) of an directional-EnginePower of (20, 10, 100, 10) at a mass
 * of 1 will result in a directional acceleration of (10, -8, -10)
 */
typedef AbstractMove EngineState;
