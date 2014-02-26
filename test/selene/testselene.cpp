#include <bandit/bandit.h>

#include <selene.h>

#include "property/propertymanager.h"


using namespace bandit;

go_bandit([]() {
    describe("Selene", []() {
        PropertyManager::instance()->reset();
        PropertyManager::instance()->load("data/config.ini");
        PropertyManager::instance()->load("data/voxels.ini", "voxels");


        it("basics", [&]() {
            sel::State state;
            AssertThat(state.Load("test/selene/test.lua"), Equals(true));
            AssertThat((int)state["foo"], Equals(4));
            AssertThat((std::string)state["bar"][3], Equals("hi"));
            AssertThat((std::string)state["bar"]["key"], Equals("there"));
        });
    });
});
