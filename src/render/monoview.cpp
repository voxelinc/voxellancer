#include "monoview.h"

#include "camera/camera.h"
#include "camera/camerahead.h"

#include "etc/windowmanager.h"

#include "render/scene.h"


MonoView::MonoView() {

}

void MonoView::resize() {

}

void MonoView::draw(Scene* scene, CameraHead* cameraHead) {
    Camera camera(WindowManager::instance()->resolution().width(), WindowManager::instance()->resolution().height());

    camera.setPosition(cameraHead->position());
    camera.setOrientation(cameraHead->orientation());

    scene->draw(&camera);
}
