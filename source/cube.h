#include "thing.h"


class Cube : public Thing {
public:
    Cube();

    virtual void draw();
    virtual void update(float delta_sec);
  
private:
    void createAndSetupShaders();
    void createAndSetupGeometry();
};