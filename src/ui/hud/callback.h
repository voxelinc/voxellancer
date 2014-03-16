
#include "ui/clicktype.h"

class Callback {
public:
    Callback();

    virtual void onClickCallback(ClickType clickType);
    virtual void onMouseOverCallback();

};