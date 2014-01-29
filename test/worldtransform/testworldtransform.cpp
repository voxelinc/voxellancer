#include <bandit/bandit.h>

#include <iostream>
#include <math.h>

#include <glm/glm.hpp>

#include "../bandit_extension/vec3helper.h"
#include "geometry/transform.h"
#include "property/propertymanager.h"

using namespace bandit;


go_bandit([](){
    describe("Transform", [](){
        PropertyManager::instance()->reset();
        PropertyManager::instance()->load("data/config.ini");

        before_each([&]() {

        });

        it("test angle calculation assumption", [&]() {

            glm::quat q1;
            glm::quat q2;
                /*x 0.324251682  float
                y - 0.124075770  float
                z   0.936692774  float
                w - 0.0455596969 float

                x   0.324240237  float
                y - 0.124073826  float
                z   0.936697066  float
                w - 0.0455590598 float
*/

            AssertThat(glm::angle(glm::inverse(q1)*q2), EqualsWithDelta(0, 0.01));

            q2 = glm::angleAxis(90.f, glm::vec3(1, 0, 0));

            AssertThat(glm::angle(glm::inverse(q1)*q2), EqualsWithDelta(90, 0.01));

            q1 = glm::angleAxis(90.f, glm::vec3(-1, 0, 0));

            AssertThat(glm::angle(glm::inverse(q1)*q2), EqualsWithDelta(180, 0.01));


            q1 = glm::quat(0.324251682f, -0.124075770f, 0.936692774f, -0.0455596969f);
            q2 = glm::quat(0.324240237f, -0.124073826f, 0.936697066f, -0.0455590598f);

            AssertThat(glm::angle(glm::inverse(q1)*q2), EqualsWithDelta(0, 0.01));

        });

        it("is finite", [&]() {
            glm::quat q1(0.153906465f, -0.0734307691f, -0.699099243f, -0.694394350f);
            glm::quat q2(-0.153925106f, 0.0733917207f, 0.698923051f, 0.694571733f);

            AssertThat(std::isfinite(glm::slerp(q1, q2, 0.0f).w), Equals(true));
            AssertThat(std::isfinite(glm::slerp(q1, q2, 0.001f).w), Equals(true));
            AssertThat(std::isfinite(glm::slerp(q1, q2, 0.5f).w), Equals(true));
            AssertThat(std::isfinite(glm::slerp(q1, q2, 1.0f).w), Equals(true));


        });

        it("applyTo(vec3) equals matrix()*vec3", [&]() {
            glm::vec3 vtest(1.0, 2.0, 3.0);
            Transform w(glm::vec3(0), 2.0);

            AssertThat(w.applyTo(vtest), EqualsWithDelta(glm::vec3(w.matrix() * glm::vec4(vtest, 1.0)), glm::vec3(0.01)));

            w.setPosition(glm::vec3(1, 2, 0));
            AssertThat(w.applyTo(vtest), EqualsWithDelta(glm::vec3(w.matrix() * glm::vec4(vtest, 1.0)), glm::vec3(0.01)));

            w.setOrientation(glm::angleAxis(20.f, glm::vec3(6.0, 3.0, 1.0)));
            AssertThat(w.applyTo(vtest), EqualsWithDelta(glm::vec3(w.matrix() * glm::vec4(vtest, 1.0)), glm::vec3(0.01)));

            w.setCenter(glm::vec3(6, 7, 0));
            AssertThat(w.applyTo(vtest), EqualsWithDelta(glm::vec3(w.matrix() * glm::vec4(vtest, 1.0)), glm::vec3(0.01)));

            w.rotate(glm::angleAxis(123.f, glm::vec3(1.0, 2.0, 3.0)));
            AssertThat(w.applyTo(vtest), EqualsWithDelta(glm::vec3(w.matrix() * glm::vec4(vtest, 1.0)), glm::vec3(0.01)));
        });


        it("test adjust center", [&]() {
            glm::vec3 vtest(5.0, 8.0, 12.0);
            glm::vec3 vdiff(1.0, 0.0, 2.0);
            Transform  w1(glm::vec3(1, 2, 3), 2.0);
            glm::quat orientation = glm::angleAxis(123.f, glm::vec3(1, 3, 5));
            w1.setOrientation(orientation);
            Transform w2(w1);

            w2.setCenterAndAdjustPosition(w1.center() - vdiff);

            AssertThat(w1.applyTo(vtest), EqualsWithDelta(w2.applyTo(vtest), glm::vec3(0.01)));
        });


        it("supports inverseApplyTo", [&]() {
            Transform t;

            t.setPosition(glm::vec3(12, -5, 3));
            t.setOrientation(glm::angleAxis(56.0f, glm::normalize(glm::vec3(2, 6, -3))));
            t.setScale(2.5f);
            t.setCenter(glm::vec3(1, 0, 0));

            glm::vec3 origVec(-13.4, 90, 5);

            glm::vec3 appliedVec = t.applyTo(origVec);
            glm::vec3 inverseAppliedVec = t.inverseApplyTo(appliedVec);

            AssertThat(origVec, EqualsWithDelta(inverseAppliedVec, glm::vec3(0.1, 0.1, 0.1)));
        });
    });
});

