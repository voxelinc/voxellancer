#define BOOST_TEST_MODULE test_property

#include <boost/test/included/unit_test.hpp>

#include <glm/glm.hpp>
#include <glow/ChangeListener.h>
#include <glow/logging.h>

#include "property/propertymanager.h"


class Listener : public glow::ChangeListener {

public:
    bool success = false;

    virtual void notifyChanged() {
        success = true;
    }

};


BOOST_AUTO_TEST_SUITE(test_property)

BOOST_AUTO_TEST_CASE(test_prop_after_load) {
    PropertyManager::clear();
    PropertyManager::getInstance()->load("test/property/test.ini");
    
    Property<int> iSize("player.size");
    Property<float> fProp("player.size");
    Property<float> fProp2("player.height");
    Property<std::string> sProp1("player.name");
    Property<std::string> sProp2("section.name");
    Property<char> cProp("section.forward");
    Property<bool> bProp2("player.is_true");
    Property<glm::vec3> v3Prop("player.pos");
    
    BOOST_CHECK_EQUAL(iSize.get(), 1);
    BOOST_CHECK_EQUAL(fProp.get(), 1);
    BOOST_CHECK_CLOSE_FRACTION(fProp2.get(), 4.51, 0.01);
    BOOST_CHECK_EQUAL(sProp1.get(), "hans");
    BOOST_CHECK_EQUAL(sProp2.get(), "peter");
    BOOST_CHECK_EQUAL(cProp.get(), 'w');
    BOOST_CHECK_EQUAL(bProp2.get(), true);
    BOOST_CHECK_EQUAL(v3Prop.get().x, 1.0);
    BOOST_CHECK_EQUAL(v3Prop.get().y, 0);
    BOOST_CHECK_EQUAL(v3Prop.get().z, .5);

    PropertyManager::clear();
}

BOOST_AUTO_TEST_CASE(test_prop_before_load) {
    glow::setVerbosityLevel(glow::LogMessage::Warning);
    PropertyManager::clear();

    Property<int> iSize("player.size");
    BOOST_CHECK_EQUAL(iSize.get(), 0);
    Property<float> fProp("player.size");
    Property<float> fProp2("player.height");
    Property<std::string> sProp1("player.name");
    Property<std::string> sProp2("section.name");
    Property<char> cProp("section.forward");
    Property<bool> bProp2("player.is_true");

    PropertyManager::getInstance()->load("test/property/test.ini");

    BOOST_CHECK_EQUAL(iSize.get(), 1);
    BOOST_CHECK_EQUAL(fProp.get(), 1);
    BOOST_CHECK_CLOSE_FRACTION(fProp2.get(), 4.51, 0.01);
    BOOST_CHECK_EQUAL(sProp1.get(), "hans");
    BOOST_CHECK_EQUAL(sProp2.get(), "peter");
    BOOST_CHECK_EQUAL(cProp.get(), 'w');
    BOOST_CHECK_EQUAL(bProp2.get(), true);

    PropertyManager::clear();
    glow::setVerbosityLevel(glow::LogMessage::Debug);
}

BOOST_AUTO_TEST_CASE(test_prop_reload) {
    PropertyManager::clear();

    PropertyManager::getInstance()->load("test/property/test.ini");
    Property<std::string> sProp("player.name");
    Property<char> cProp("section.forward");

    BOOST_CHECK_EQUAL(sProp.get(), "hans");
    BOOST_CHECK_EQUAL(cProp.get(), 'w');

    PropertyManager::getInstance()->load("test/property/test2.ini");
    BOOST_CHECK_EQUAL(sProp.get(), "hans meier");
    BOOST_CHECK_EQUAL(cProp.get(), 'x');

    PropertyManager::clear();
}

BOOST_AUTO_TEST_CASE(test_prop_callback) {
    
    PropertyManager::getInstance()->load("test/property/test.ini");

    Listener listener;
    PropertyManager::getInstance()->registerListener(&listener);
    
    BOOST_CHECK_EQUAL(listener.success, false);

    PropertyManager::getInstance()->load("test/property/test.ini");

    BOOST_CHECK_EQUAL(listener.success, true);

    PropertyManager::clear();
}




BOOST_AUTO_TEST_SUITE_END()
