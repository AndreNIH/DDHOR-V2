#pragma once
#include "../PopupLayer.h"
#include "../TextboxUtils.h"
#include "../Widget/ListWidget.h"
#include "LoadLayerDelegate.h"
class LoadMenuLayer : public PopupLayer, gd::TextInputDelegate, DropdownListDelegate, gd::FLAlertLayerProtocol, public LoaderProtocol{
private:
	gd::CCTextInputNode* m_macroNameInput = nullptr;
	DropdownList* m_fileDropdown = nullptr;
	cocos2d::CCLabelBMFont* m_errorLabel = nullptr;
	//Handlers-delegates
	void textInputOpened(gd::CCTextInputNode* sender) override { m_errorLabel->setVisible(false); }
	void textChanged(gd::CCTextInputNode* sender) override;
	void dropdownItemSelected(ListItem* item) override;
	void scrollWheel(float x, float y) override;
	void ccTouchEnded(cocos2d::CCTouch* pTouch, cocos2d::CCEvent* pEvent) override;
	void onMacroBrowser(cocos2d::CCObject* sender);

	void onLoad(cocos2d::CCObject* sender);
	std::vector<std::string> getMacroFiles();


public:
	void setup() override;
	static LoadMenuLayer* create(float width, float height, const char* bgName = "GJ_square01.png");
};