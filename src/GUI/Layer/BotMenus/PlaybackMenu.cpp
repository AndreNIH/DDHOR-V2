#include "PlaybackMenu.h"
#include <GUI/Widget/DropdownList.h>
PlaybackMenu::PlaybackMenu() : PopupLayer({350, 200}, "GJ_square03.png"){}

bool PlaybackMenu::setup(){
    auto size = CCDirector::sharedDirector()->getWinSize();
    auto dropdown = widget::DropdownList::create();
    dropdown->add("Lorem Ipsum");
    dropdown->add("Lorem Ipsum");
    dropdown->add("Lorem Ipsum");
    dropdown->add("Lorem Ipsum");
    dropdown->add("Lorem Ipsum");
    dropdown->add("Lorem Ipsum");
    dropdown->setSize({340,20}); //todo: 
    dropdown->refresh();
    dropdown->setPosition(size.width/2, size.height/2);
    addChild(dropdown);
    return true;
}