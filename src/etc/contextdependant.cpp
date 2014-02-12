#include "contextdependant.h"

#include "etc/windowmanager.h"

ContextDependant::ContextDependant() {
    WindowManager::instance()->registerContextDependant(this);
}

ContextDependant::~ContextDependant() {
    WindowManager::instance()->unRegisterContextDependant(this);

}