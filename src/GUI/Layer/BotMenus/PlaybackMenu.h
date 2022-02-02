#pragma once
#include "../PopupLayer.h"

class PlaybackMenu : public PopupLayer{
private:
    //void onLoad();    
    bool setup() override;
public:
    PlaybackMenu();
    CREATE_FUNC(PlaybackMenu);
};