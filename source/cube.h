#include "thing.h"


class Cube : public Thing {
public:
    Cube();

	virtual void draw();
	virtual void drawtest(glm::mat4 projection);
    virtual void update(float delta_sec);
  
private:
    void createAndSetupShaders();
    void createAndSetupGeometry();
};