#include "hudget.h"

#include "hud.h"


Hudget::Hudget(HUD* hud):
    m_hud(hud)
{
}


HUD* Hudget::hud() {
    return m_hud;
}
