#pragma once
#include "../PopupLayer.h"

class RecorderMenu : public PopupLayer{
private:
    void onDropdownList();
    void onRecord();
    bool setup() override;
public:
    RecorderMenu();
    CREATE_FUNC(RecorderMenu);
};