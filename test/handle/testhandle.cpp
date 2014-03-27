#include <bandit/bandit.h>

#include <iostream>
#include <list>

#include "../bandit_extension/vec3helper.h"
#include "worldobject/worldobject.h"
#include "world/handler/splitdetector.h"
#include "world/handler/splitter.h"
#include "property/propertymanager.h"
#include "utils/handle/handle.h"
#include "world/helper/splitdata.h"
#include "voxel/voxel.h"


using namespace bandit;

namespace {
class Foo {
public:
    Foo(): m_handle(this)
    {

    }

    Handle<Foo>& handle() {
        return m_handle;
    }

protected:
   Handle<Foo> m_handle;
};
}

go_bandit([]() {
    describe("Handle", []() {
        PropertyManager::instance()->reset();
        PropertyManager::instance()->load("data/config.ini");
        PropertyManager::instance()->load("data/voxels.ini", "voxels");

        before_each([&]() {

        });

        it("Handle from pointer is root", [&]() {
            Foo foo;
            AssertThat(foo.handle().root(), Equals(true));
        });

        it("Root-handle gets invalidated on delete", [&]() {
            Foo* foo = new Foo;
            Handle<Foo> handle(foo->handle());

            AssertThat(handle.valid(), Equals(true));
            delete foo;
            AssertThat(handle.valid(), Equals(false));
        });
    });
});
