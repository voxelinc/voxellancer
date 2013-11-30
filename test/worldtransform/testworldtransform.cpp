#include <bandit/bandit.h>

#include <iostream>
#include <math.h>

#include <glm/glm.hpp>

#include "../bandit_extension/vec3helper.h"
#include "worldtransform.h"

using namespace bandit;


go_bandit([](){
    describe("WorldTransform", [](){
        
        before_each([&]() {

        });

        it("test angle calculation assumption", [&]() {

            glm::quat q1;
            glm::quat q2;
                /*x	0.324251682	float
                y - 0.124075770	float
                z	0.936692774	float
                w - 0.0455596969	float

                x	0.324240237	float
                y - 0.124073826	float
                z	0.936697066	float
                w - 0.0455590598	float
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

        it("applyTo(vec3) equals matrix()*vec3", [&]() {
            glm::vec3 vtest(1.0, 2.0, 3.0);
            WorldTransform w(glm::vec3(0), 2.0);            
            
            AssertThat(w.applyTo(vtest), EqualsWithDelta(glm::vec3(w.matrix() * glm::vec4(vtest, 1.0)), glm::vec3(0.01, 0.01, 0.01)));

            w.setPosition(glm::vec3(1, 2, 0));
            AssertThat(w.applyTo(vtest), EqualsWithDelta(glm::vec3(w.matrix() * glm::vec4(vtest, 1.0)), glm::vec3(0.01, 0.01, 0.01)));

            w.setOrientation(glm::angleAxis(20.f, glm::vec3(6.0, 3.0, 1.0)));
            AssertThat(w.applyTo(vtest), EqualsWithDelta(glm::vec3(w.matrix() * glm::vec4(vtest, 1.0)), glm::vec3(0.01, 0.01, 0.01)));
            
            w.setCenter(glm::vec3(6, 7, 0));
            AssertThat(w.applyTo(vtest), EqualsWithDelta(glm::vec3(w.matrix() * glm::vec4(vtest, 1.0)), glm::vec3(0.01, 0.01, 0.01)));

            w.rotate(glm::angleAxis(123.f, glm::vec3(1.0, 2.0, 3.0)));
            AssertThat(w.applyTo(vtest), EqualsWithDelta(glm::vec3(w.matrix() * glm::vec4(vtest, 1.0)), glm::vec3(0.01, 0.01, 0.01)));
        });

    });
});

