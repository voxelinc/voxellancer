#pragma once

#include "propertycollection.h"

template <class T>
void PropertyManager::registerProperty(Property<T> * prop)
{
    getPropertyCollection(prop)->registerProperty(prop);
}

template <class T>
void PropertyManager::unregisterProperty(Property<T> * prop)
{
    getPropertyCollection(prop)->unregisterProperty(prop);
}
