#pragma once
#include <gd.h>
#include <cocos-ext.h>

namespace TextUtil{
    cocos2d::extension::CCScale9Sprite* createTextTint(gd::CCTextInputNode* input);
	cocos2d::CCLabelBMFont* createTextLabel(const std::string& label, gd::CCTextInputNode* input);
}