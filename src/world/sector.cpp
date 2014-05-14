#include "sector.h"


Sector::Sector(const std::string& name, Universe* universe):
    m_name(name),
    m_universe(universe)
{

}

Sector::~Sector() = default;

const std::string& Sector::name() const {

}

Universe* Sector::universe(){

}


std::list<glow::ref_ptr<FunctionalWorldElement>>& Sector::functionalElements(){

}

std::list<glow::ref_ptr<FunctionalWorldElement>>& Sector::physicalElements() {

}


void Sector::addElement(FunctionalWorldElement* element) {

}

void Sector::addElement(PhysicalWorldElement* element){

}


void Sector::update(float deltaSec) {

}

