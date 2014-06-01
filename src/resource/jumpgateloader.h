#pragma once

#include "universe/jumpgate.h"


class JumpgateLoader {
public:
    JumpgateLoader(const std::string& group);
    virtual ~JumpgateLoader();

    glow::ref_ptr<Jumpgate>& jumpgate();
    const std::string& targetSector();
    int buddy();


protected:
    std::string& group;

    bool m_loaded;

    glow::ref_ptr<Jumpgate> m_jumpgate;
    std::string m_targetSector;
    int m_buddy;


    void loadLazy();
};

