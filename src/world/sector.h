#pragma once

#include <string>


class FunctionalWorldElement;
class PhysicalWorldElement;
class Universe;

class Sector {
public:
    Sector(const std::string& name, Universe* universe);
    virtual ~Sector();

    const std::string& name() const;
    Universe* universe();

    std::list<glow::ref_ptr<FunctionalWorldElement>>& functionalElements();
    std::list<glow::ref_ptr<FunctionalWorldElement>>& physicalElements();

    void addElement(FunctionalWorldElement* element);
    void addElement(PhysicalWorldElement* element);

    void update(float deltaSec);


protected:
    std::string m_name;
    Universe* m_universe;

    std::list<glow::ref_ptr<UniverseElements>> m_functionalElements;
    std::list<glow::ref_ptr<PhysicalWorldElement>> m_physicalElements;
};

