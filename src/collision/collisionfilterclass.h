#pragma once


enum class CollisionFilterClass {
    Bullet              = 1 << 0,
    Rocket              = 1 << 1,
    Ship                = 1 << 2,
    ExplosionParticle   = 1 << 3,
    Other               = 1 << 4
};


