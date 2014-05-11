#include "enginebuilder.h"

#include "property/property.h"

#include "equipment/engine.h"


EngineBuilder::EngineBuilder(const std::string& name):
    m_name(name)
{
}

Engine* EngineBuilder::build() {
    /*
     * Currently there are no special implementations, so every name
     * will be resolved to a normal Engine loaded from properties
     */
    Engine* engine = new Engine(m_name);

    engine->setVisuals(Visuals::fromProperties(m_name + ".visuals"));
    engine->setPower(EnginePower::fromProperties(m_name  + ".general"));
    engine->setEngineSound(SoundProperties::fromProperties(m_name + ".sound"));

    return engine;
}

