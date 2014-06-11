#include "shieldbuilder.h"

#include "property/property.h"

#include "equipment/shield.h"


ShieldBuilder::ShieldBuilder(const std::string& name):
    m_name(name)
{

}

Shield* ShieldBuilder::build() {
    /*
        Currently there are no special implementations, so every name
        will be resolved to a normal Shield
    */
    Shield* shield = new Shield(m_name);

    shield->setRegeneration(Property<float>::get(m_name + ".general.regeneration"));
    shield->setMaxHP(Property<float>::get(m_name + ".general.hp"));

    return shield;
}

