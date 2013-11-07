#pragma once

// Includes from the c/c++ stdlibrary. For C headers, use the c* version
#include <cstdlib>
#include <iostream>
#include <cmath>

// Includes from 3rd party libraries, grouped by lib
#include <glm/glm.hpp>
#include <glow/Camera.h>
#include <glow/Program.h>
#include <gl/glew.h>

// Includes from modules of voxellances, grouped by module
#include "utils/tostring.h"
#incldue "worldtree/worldtree.h"
#include "worldtree/worldtreenode.h"

// Includes from this module
#include "anotherstyleguide.h"


// After 2 newlines, forward-declarations
class YetAnotherStyleguide;

class StyleGuide : public A, public B, private C
{
public:
    StyleGuide()
    virtual ~StyleGuide();
    
    const Value &value() const;
    void setValue(const Value &value) const;
    
// 2 newlines after last public member  
protected:


// 2 newlines after last protected member  
// Only make private if really necessary 
private:
    
};
