#include "jumpgate.h"


Jumpgate::Jumpgate() = default;

Jumpgate::~Jumpgate() = default;

Jumpgate* Jumpgate::buddy() {
    return m_buddy.get();
}

void Jumpgate::setBuddy(Jumpgate* buddy) {
    m_buddy = makeHandle(buddy);
}

