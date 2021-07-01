#pragma once
#include "../PopupLayer.h"
#include "LoadLayerDelegate.h"
#include <cocos-ext.h>
#include <gd.h>

class RecordMenuLayer : public PopupLayer, gd::FLAlertLayerProtocol, public LoaderProtocol {
private:
	cocos2d::CCLabelBMFont* m_macroNameLabel = nullptr;
	gd::CCTextInputNode* m_macroNameInput = nullptr;
	gd::CCTextInputNode* m_fpsInput = nullptr;
	

	
	void startRecording();

	void FLAlert_Clicked(gd::FLAlertLayer*, bool btn2) override;
	void onRecord(cocos2d::CCObject* sender);
public:
	void setup() override;
	static RecordMenuLayer* create(float width, float height, const char* bgName = "GJ_square01.png");
};