#pragma once
#include <gd.h>
#include "../UI/Menu/BMenuLayer.h"

namespace GUI {
	namespace Widget {
		class LoadingButton : public cocos2d::CCMenuItemSprite, public LoaderProtocol{
		private:
			LoaderDelegate* m_loaderDelegate;
			cocos2d::CCAnimate* m_loadAnim = nullptr;
			float m_sizeMult = 1.0f;
			static const std::string defaultSprite;
			
			static const int MENULAYER_TAG = 1006;
			//Legacy
			static const int BOUNCE_SEQ_TAG = 1004;
			static const int LOAD_SEQ_TAG = 1005;
			

			static cocos2d::CCSprite* getDefaultSprite() {return cocos2d::CCSprite::createWithSpriteFrameName("GJ_playBtn2_001.png"); }
			cocos2d::CCAnimate* getLoadAnimation();
			void beginMenuLoading();
			void endMenuLoading();

		protected:
			void invokeLoader(cocos2d::CCObject* extra);
			void selected() override;
			void unselected() override;
			void activate() override;

		public:
			void setSizeMult(float mult) { m_sizeMult = mult; }
			static LoadingButton* create(cocos2d::CCObject* target);
			~LoadingButton() { std::cout << "LOADINGBUTTON DESTROYED\n"; }

		};
	}
}