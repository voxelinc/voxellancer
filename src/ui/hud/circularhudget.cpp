#include "circularhudget.h"

#include "geometry/sphere.h"
#include "geometry/ray.h"


CircularHudget::CircularHudget(HUD* hud, float radius):
    Hudget(hud),
    m_radius(radius)
{
}

float CircularHudget::radius() const {
    return m_radius;
}

bool CircularHudget::isAt(const Ray& ray) const {
    return ray.intersects(Sphere(worldPosition(), m_radius));
}

