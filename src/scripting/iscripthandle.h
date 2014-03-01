#pragma once


class Scriptable;

class IScriptHandle {
public:
    virtual Scritable* scriptable() = 0;
};
