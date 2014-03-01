#pragma once

#include <type_traits>

#include "utils/handle/handle.h"


template<typename T>
class ScriptHandle: public IScriptHandle {
public:
    static_assert(std::is_base_of<Scriptable, T>::value, "ScriptHandle can only hold Scriptable derivates");

    ScriptHandle(T* scriptable);

    virtual bool valid() const override;
    virtual void invalidate() override;

    virtual Scriptable* scriptable() override;


protected:
    Handle<T> m_handle;
};


#include "scripthandle.inl"
