#include "scriptengine.h"

#include <stdexcept>

#include <glow/logging.h>


template<class T>
T* ScriptEngine::get(int key) {
    Scriptable* scriptable = getScriptable(key);
    if (!scriptable) {
        return nullptr;
    }

    T* object = dynamic_cast<T*>(scriptable);

    if (object != nullptr) {
        return object;
    } else {
        glow::warning("ScriptEngine: script-key '%;' of type '%;' is no '%;'", key, typeid(*scriptable).name(), typeid(T).name());
        throw new std::runtime_error("ScriptEngine: invalid type requested");
    }
}
