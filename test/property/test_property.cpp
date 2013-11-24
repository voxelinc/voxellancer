#include <bandit/bandit.h>

#include <glm/glm.hpp>
#include <glow/ChangeListener.h>
#include <glow/logging.h>

#include "property/propertymanager.h"

using namespace bandit;





go_bandit([](){
    class Listener : public glow::ChangeListener {
    public:
        bool success = false;

        virtual void notifyChanged() {
            success = true;
        }
    };

    describe("Property", [](){
        before_each([&](){
            glow::setVerbosityLevel(glow::LogMessage::Fatal);
            PropertyManager::reset();
        });
        after_each([&](){
            glow::setVerbosityLevel(glow::LogMessage::Info);
        });

        it("should load", [&]() {
            PropertyManager::instance()->load("test/property/test.ini");
    
            Property<int> iSize("player.size");
            Property<float> fProp("player.size");
            Property<float> fProp2("player.height");
            Property<std::string> sProp1("player.name");
            Property<std::string> sProp2("section.name");
            Property<char> cProp("section.forward");
            Property<bool> bProp2("player.is_true");
            Property<glm::vec3> v3Prop("player.pos");
    
            AssertThat(iSize.get(), Equals(1));
            AssertThat(fProp.get(), Equals(1));
            AssertThat(fProp2.get(), EqualsWithDelta(4.51, 0.01));
            AssertThat(sProp1.get(), Equals("hans"));
            AssertThat(sProp2.get(), Equals("peter"));
            AssertThat(cProp.get(), Equals('w'));
            AssertThat(bProp2.get(), Equals(true));
            AssertThat(v3Prop.get().x, Equals(1.0));
            AssertThat(v3Prop.get().y, Equals(0));
            AssertThat(v3Prop.get().z, Equals(.5));
        });

        it("should work before load", [&]() {
            // suppress property not found debug info
            glow::setVerbosityLevel(glow::LogMessage::Fatal);

            Property<int> iSize("player.size");
            AssertThat(iSize.get(), Equals(0));
            Property<float> fProp("player.size");
            Property<float> fProp2("player.height");
            Property<std::string> sProp1("player.name");
            Property<std::string> sProp2("section.name");
            Property<char> cProp("section.forward");
            Property<bool> bProp2("player.is_true");

            PropertyManager::instance()->load("test/property/test.ini");

            AssertThat(iSize.get(), Equals(1));
            AssertThat(fProp.get(), Equals(1));
            AssertThat(fProp2.get(), EqualsWithDelta(4.51, 0.01));
            AssertThat(sProp1.get(), Equals("hans"));
            AssertThat(sProp2.get(), Equals("peter"));
            AssertThat(cProp.get(), Equals('w'));
            AssertThat(bProp2.get(), Equals(true));

            glow::setVerbosityLevel(glow::LogMessage::Debug);
        });

        it("should reload", [&]() {
            PropertyManager::instance()->load("test/property/test.ini");
            Property<std::string> sProp("player.name");
            Property<char> cProp("section.forward");

            AssertThat(sProp.get(), Equals("hans"));
            AssertThat(cProp.get(), Equals('w'));

            PropertyManager::instance()->load("test/property/test2.ini");
            AssertThat(sProp.get(), Equals("hans meier"));
            AssertThat(cProp.get(), Equals('x'));
        });

        it("should call a callback", [&]() {
            PropertyManager::instance()->load("test/property/test.ini");

            Listener listener;
            PropertyManager::instance()->registerListener(&listener);
            AssertThat(listener.success, Equals(false));
            PropertyManager::instance()->load("test/property/test.ini");
            AssertThat(listener.success, Equals(true));

        });
    });
});

