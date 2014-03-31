#pragma once


template<typename ...Args>
std::shared_ptr<Callback> Bindings::createCallback(const std::string& function, Args... args) {
    return std::make_shared<ScriptCallback<Args...>>(m_script, function, args...);
}


