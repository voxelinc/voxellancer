#pragma once


class Scriptable;

class IScriptHandle {
public:
    virtual bool valid() = 0;



    virtual Scritable* scriptable() = 0;
};
