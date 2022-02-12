#include "PlaybackMenu.h"
#include <GUI/Widget/DropdownList.h>
#include <GUI/Widget/Textbox.h>
#include <spdlog/spdlog.h>
PlaybackMenu::PlaybackMenu() : PopupLayer({350, 200}, "GJ_square03.png"){}

bool PlaybackMenu::setup(){
    auto size = CCDirector::sharedDirector()->getWinSize();
    auto dropdown = widget::DropdownList::create();
    const float textboxWidth  = _layerDimensions.width * 0.80f;
    const float textboxHeight = _layerDimensions.height * 0.15f;

    if(dropdown == nullptr) return false;
    dropdown->add("Lorem Ipsum");
    dropdown->add("Lorem Ipsum");
    dropdown->add("Lorem Ipsum");
    dropdown->add("Lorem Ipsum");
    dropdown->add("Lorem Ipsum");
    dropdown->add("Lorem Ipsum");
    dropdown->setMaxDisplayItems(3);
    dropdown->setSize({textboxWidth,textboxHeight*0.8f});
    dropdown->refresh();
    
    
    widget::TextboxBuilder textboxBuilder;
    textboxBuilder.setBackground("square02_small.png", 100);
    textboxBuilder.setCaption("Macro Name");
    textboxBuilder.setFont("chatFont.fnt");
    textboxBuilder.setSize(textboxWidth,textboxHeight);
    widget::Textbox* textbox = textboxBuilder.createTextInput(this);
    if(!textbox) return nullptr;
    textbox->setPositionX(size.width/2);
    textbox->setPositionY(size.height/2+20);
    dropdown->bindToTextbox(textbox->getTextInput());
    dropdown->bindTextEditedCallback(nullptr);
    dropdown->setPositionX(size.width/2);
    dropdown->setAnchorPoint({0.5f, 1.0f});
    dropdown->setPositionY(textbox->getPositionY()-textbox->getContentSize().height/2);
    spdlog::trace("Textbox content size is ({},{})", textbox->getScaledContentSize().width,  textbox->getScaledContentSize().height);
    addChild(dropdown);
    addChild(textbox);
    return true;
}