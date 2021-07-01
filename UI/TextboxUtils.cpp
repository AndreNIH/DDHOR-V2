#include "TextboxUtils.h"
using namespace cocos2d;

extension::CCScale9Sprite* TextUtil::createTextTint(gd::CCTextInputNode* input) {
    auto tint = extension::CCScale9Sprite::create("square02_small.png", { 0,0, 40, 40 });
    tint->setContentSize(input->getContentSize());
    tint->setPosition(input->getPosition());
    tint->setOpacity(100);
    return tint;
}

CCLabelBMFont* TextUtil::createTextLabel(const std::string& label, gd::CCTextInputNode* input)
{
    auto bmfLabel = CCLabelBMFont::create(label.c_str(), "bigFont.fnt", 100, CCTextAlignment::kCCTextAlignmentLeft);
    bmfLabel->setScale(0.5);
    bmfLabel->setWidth(input->getContentSize().width);
    bmfLabel->setPositionY(input->getPositionY() + (bmfLabel->getScaledContentSize().height / 2) + 20);
    bmfLabel->setPositionX((input->getPositionX() / 2) + bmfLabel->getScaledContentSize().width / 2);
    return  bmfLabel;
}

