#include "enginebuilder.h"

#include "property/property.h"

#include "equipment/engine.h"
#include "equipment/engines/genericengine.h"


EngineBuilder::EngineBuilder(const std::string& name):
    m_name(name)
{
}

Engine* EngineBuilder::build() {
    /*
        Currently there are no special implementations, so every name
        will be resolved to a GenericEngine
    */
    GenericEngine* genericEngine = new GenericEngine(m_name);

    genericEngine->setVisuals(Visuals::fromProperties(m_name + ".visuals"));
    genericEngine->setPower(EnginePower::fromProperties(m_name  + ".general"));
    genericEngine->setEngineSound(SoundProperties::fromProperties(m_name + ".sound"));

    return genericEngine;
}

