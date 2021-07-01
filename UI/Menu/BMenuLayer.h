#pragma once
#include "../PopupLayer.h"
#include "LoadLayerDelegate.h"

namespace GUI {
	//FWD Declare GD Level loader delegates
	class BMenuLayer : public PopupLayer, public LoaderProtocol {
	private:
		void onNormalLoad(cocos2d::CCObject* caller);
		void onReplayLoad(cocos2d::CCObject* caller);
		void onRecordLoad(cocos2d::CCObject* caller);
		void onOptions(cocos2d::CCObject* extra);
		
	public:
		void setup() override;
		static BMenuLayer* create(float width, float height, const char* bgName = "GJ_square01.png");
		~BMenuLayer() { std::cout << "BMENULAYER DESTROYED\n"; }
	};
}