#include "enginebuilder.h"

#include "property/property.h"

#include "worldobject/components/engine.h"
#include "worldobject/components/engines/genericengine.h"


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
    genericEngine->setEngineSound(SoundProps::fromProperties(m_name + ".sound"));

    return genericEngine;
}

