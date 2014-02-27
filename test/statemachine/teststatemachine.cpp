#include <bandit/bandit.h>

#include <iostream>
#include <list>

#include "../bandit_extension/vec3helper.h"
#include "worldobject/worldobject.h"
#include "world/handler/splitdetector.h"
#include "world/handler/splitter.h"
#include "property/propertymanager.h"
#include "world/helper/splitdata.h"
#include "voxel/voxel.h"
#include "utils/statemachine/state.h"
#include "utils/statemachine/transition.h"
#include "utils/statemachine/triggeredtransition.h"


using namespace bandit;

class TestState : public State {
public:
    TestState(const std::string& name, State* parent): State(name, parent) {
    }
};

class B: public TestState {
public:
    B(State* parent): TestState("B", parent) {
    }
};

class C: public TestState {
public:
    C(State* parent): TestState("C", parent) {
    }
};

class D: public TestState {
public:
    D(State* parent): TestState("D", parent) {
    }
};

class E: public TestState {
public:
    E(State* parent): TestState("E", parent) {
    }
};

class F: public TestState {
public:
    F(State* parent): TestState("F", parent) {
    }
};

class G: public TestState {
public:
    G(State* parent): TestState("G", parent) {
    }
};

go_bandit([]() {
    describe("Statemachine", []() {
        PropertyManager::instance()->reset();
        PropertyManager::instance()->load("data/config.ini");
        PropertyManager::instance()->load("data/voxels.ini", "voxels");

        State *machine;
        B* b;
        C* c;
        D* d;
        E* e;
        F* f;
        G* g;

        before_each([&]() {
            machine = new State("Main");

            b = new B(machine);
            c = new C(machine);
            d = new D(b);
            e = new E(b);
            f = new F(c);
            g = new G(e);

        //    machine->setInitialSubState(b);
        });

        after_each([&]() {
            delete machine;
        });

        it("basic state", [&]() {
            machine->update(1.0f);
            AssertThat(machine->currentSubState(), Equals(b));
            AssertThat(b->currentSubState(), Equals(d));
        });

        it("basic transition", [&]() {
            TriggeredTransition* t = new TriggeredTransition(b, c);
            t->trigger();
            machine->update(1.0f);
            AssertThat(machine->currentSubState(), Equals(c));
            AssertThat(c->currentSubState(), Equals(f));
        });

        it("basic transition", [&]() {
            TriggeredTransition* t1 = new TriggeredTransition(b, c);
            TriggeredTransition* t2 = new TriggeredTransition(c, g);
            t1->trigger();
            t2->trigger();
            machine->update(1.0f);
            machine->update(1.0f);
            AssertThat(machine->currentSubState(), Equals(b));
            AssertThat(b->currentSubState(), Equals(e));
            AssertThat(e->currentSubState(), Equals(g));
        });
    });
});
