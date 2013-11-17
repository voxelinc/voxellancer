#include <bandit/bandit.h>

#include <iostream>
#include <math.h>

#include <glm/glm.hpp>

#include "utils/vec3helper.h"
#include "worldtransform.h"

using namespace bandit;


go_bandit([](){
    describe("WorldTransform", [](){
        
        before_each([&]() {

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

