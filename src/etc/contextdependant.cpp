#include "contextdependant.h"

#include "etc/contextprovider.h"

ContextDependant::ContextDependant() {
    ContextProvider::instance()->registerContextDependant(this);
}

ContextDependant::~ContextDependant() {
    ContextProvider::instance()->unregisterContextDependant(this);

}