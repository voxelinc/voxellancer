#include <bandit/bandit.h>

#include <memory>

#include <glm/glm.hpp>

#include "../bandit_extension/vec3helper.h"
#include "scripting/script.h"


using namespace bandit;


go_bandit([](){
 
    describe("Scripting vec3 lib", []() {

        std::unique_ptr<Script> script;

        before_each([&]() {
            script.reset(new Script());
        });

        it("can set debug status", [&]() {
            AssertThat(script->debugStatus(), Equals(""));
            script->loadString(R"( 
                setDebugStatus("success") 
            )");
            AssertThat(script->debugStatus(), Equals("success"));
        });

        it("can create vec3", [&]() {
            AssertThat(script->debugStatus(), Equals(""));
            script->loadString(R"( 
                v = vec3(1,2,3)
                setDebugStatus(vstring(v)) 
            )");
            AssertThat(script->debugStatus(), Equals("vec3(1, 2, 3)"));
        });

        it("can add vec3", [&]() {
            AssertThat(script->debugStatus(), Equals(""));
            script->loadString(R"( 
                x = vadd(vec3(10,20,30), vec3(1,2,3))
                setDebugStatus(vstring(x))
            )");
            AssertThat(script->debugStatus(), Equals("vec3(11, 22, 33)"));
        });

        it("can calculate vec3 lenght", [&]() {
            AssertThat(script->debugStatus(), Equals(""));
            script->loadString(R"( 
                x = vec3(1,4,9)
                l = vlength(v)
                setDebugStatus(l)
            )");
            AssertThat(atof(script->debugStatus().c_str()), EqualsWithDelta(glm::length(glm::vec3(1,4,9)), 0.001f));
        });
    });
});

