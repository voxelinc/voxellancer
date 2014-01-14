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


/*
After 2 newlines, forward-declarations
Use forward-declarations as often as possible
because they can speed up compilation
*/
class SomeForwardDeclarations;

class StyleGuide : public A, public B, private C
{
public:
    StyleGuide();
    /*
        Declare destructors only if they are needed, make them virtual only if the class contains other virtual
        members
    */
    virtual ~StyleGuide();

    const Value& value() const;
    void setValue(const Value &value);

    /*
    Declare every method that overrides a virtual method from the base-class
    as virtual and, very important, override
    */
    virtual void update() override;

    /*
        For member-functions, try to keep these general rules
        -> Order: Constructors -> Destructor -> Getters/Setters -> other operations
        -> Group functions (i.e.: don't put newlines between them) if they are getter
            and setter for the same member or are otherwise related (addVoxel and removeVoxel, e.g.)
    */

// 2 newlines after last public member
protected:


// 2 newlines after last protected member
// Only make private if really necessary
private:
    Foo m_somePrivateMember;

    void somePrivateFunction();
};

