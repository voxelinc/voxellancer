#include "styleguide.h"


// After two newlines...
StyleGuide::StyleGuide():
    m_somePrivateMember(1337)
{ // { in newline if there the stuff above doesn't fit into one line, applies to every method, not only constructors

}

StyleGuide::~StyleGuide() {

}

const Value& StyleGuide::value() const {
    return m_value;
}

void StyleGuide::setValue(const Value &value) {
    m_value = value;
}

void StyleGuide::update() {
    if (m_worldIsSaved) { // Always enclose blocks with {}, even if they are only 1 line long
        saveWorld();
    }

    for (int x = 0; x < 10; x++) {
        x += 1;
        foo();
    }

    for (Foo* foo : m_allFoos) {
        dontGiveA(foo);
    }

    switch (seats) {
    case Taken:
    break;

    default:
        takeSeat();
    }

    while (true) {
        rofl();
    }
}




