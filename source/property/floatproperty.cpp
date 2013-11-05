#include "floatproperty.h"
#include "propertymanager.h"

FloatProperty::FloatProperty(char * name):
    m_name(name),
    m_value(0)
{
    PropertyManager::getInstance()->registerFloatProp(this);
}

FloatProperty::~FloatProperty()
{
    PropertyManager::getInstance()->unregisterFloatProp(this);
}

char * FloatProperty::name()
{
    return m_name;
}

float FloatProperty::get()
{
    return m_value;
}

void FloatProperty::set(float value)
{
    m_value = value;
}

FloatProperty::operator float()
{
    return m_value;
}
