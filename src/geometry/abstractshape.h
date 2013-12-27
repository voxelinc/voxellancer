#pragma once

class Sphere;
template<typename T> class TAABB;
class WorldTransform;

class AbstractShape {
public:
    virtual bool intersects(const Sphere& sphere) const = 0;
    virtual bool nearTo(const TAABB<float>& aabb) const = 0;
    virtual bool containedBy(const TAABB<float>& aabb) const = 0;
};

