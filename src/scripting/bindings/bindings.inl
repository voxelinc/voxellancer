#pragma once


template<typename... Args>
Callback Bindings::createCallback(const std::string& function, Args... args) {
    return ScriptCallback<Args...>(m_script, function, args...);
}


