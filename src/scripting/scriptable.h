#pragma once


enum class ScriptableType {
    Squad,
    WorldObject,
    Ship,
    Other
};

class Scriptable {
public:
    Scriptable();
    
    virtual ScriptableType type() const = 0;
    
    int scriptKey() const;
    void setScriptKey(int key);
    

protected:
    int m_key;
};

