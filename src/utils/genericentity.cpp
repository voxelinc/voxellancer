#include "genericentity.h"


GenericEntity::GenericEntity(const std::string& propertyPrefix):
    m_propertyPrefix(propertyPrefix)
{
}

const std::string& GenericEntity::propertyPrefix() const {
    return m_propertyPrefix;
}
