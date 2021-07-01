#include "LoadingButton.h"
#include <algorithm>
#include <fmt/format.h>

using namespace cocos2d;

namespace GUI {

	namespace Widget {
		CCAnimate* LoadingButton::getLoadAnimation() {
			//Initialize frames
			CCArray* frames = CCArray::create();
			CCSpriteFrameCache* cache = CCSpriteFrameCache::sharedSpriteFrameCache();
			std::vector<std::string>spriteNames(31);
			std::generate(
				spriteNames.begin(),
				spriteNames.end(),
				[n = 0]() mutable {
				return fmt::format("GJ_loadPlayBtn_{:03}.png", n++);
			});

			for (auto& fn : spriteNames) {
				CCSpriteFrame* frame = cache->spriteFrameByName(fn.c_str());
				if (frame) frames->addObject(frame);
			}
			CCAnimation* animation = CCAnimation::createWithSpriteFrames(frames, 1.0 / 60.0);
			CCAnimate* animate = CCAnimate::create(animation);
			return animate;
		}

		void LoadingButton::beginMenuLoading(){
			
			
			auto actions = CCArray::create();
			actions->addObject(getLoadAnimation());
			actions->addObject(CCCallFunc::create(this, callfunc_selector(LoadingButton::endMenuLoading)));
			actions->setTag(LOAD_SEQ_TAG);
			m_pNormalImage->runAction(CCSequence::create(actions));
			m_pNormalImage->setPosition({ m_pNormalImage->getPositionX() - 2,m_pNormalImage->getPositionY() - 4 });
		}

		void LoadingButton::endMenuLoading(){
			setEnabled(false);
			auto scene = CCDirector::sharedDirector()->getRunningScene();
			auto menu = GUI::BMenuLayer::create(350, 200);
			menu->setLoaderContext(LoaderProtocol::getLoaderContext());
			menu->setTag(MENULAYER_TAG);
			scene->addChild(menu, 2);
			unselected();
			setEnabled(true);
		}

		void LoadingButton::selected() {
			//Gross
			auto layer = reinterpret_cast<CCLayer*>(CCDirector::sharedDirector()->getRunningScene()->getChildren()->objectAtIndex(0));
			layer->setKeyboardEnabled(false);
			
			auto resize = cocos2d::CCScaleTo::create(0.3, m_sizeMult);
			auto bounce = cocos2d::CCEaseBounceOut::create(resize);
			auto bounceActions = CCArray::create();
			bounceActions->addObject(bounce);
			bounceActions->addObject(CCDelayTime::create(0.5));
			bounceActions->addObject(CCCallFunc::create(this, callfunc_selector(LoadingButton::beginMenuLoading)));
			runAction(CCSequence::create(bounceActions))->setTag(BOUNCE_SEQ_TAG);
			CCMenuItemSprite::selected();
		}

		void LoadingButton::unselected() {
			auto layer = reinterpret_cast<CCLayer*>(CCDirector::sharedDirector()->getRunningScene()->getChildren()->objectAtIndex(0));
			layer->setKeyboardEnabled(true);
			CCMenuItemSprite::unselected();
			m_pNormalImage->stopAllActions();
			m_pNormalImage->setPosition({ 0,51 });
			stopAllActions();
			auto resize = cocos2d::CCScaleTo::create(0.3, 1.0);
			auto bounce = cocos2d::CCEaseBounceOut::create(resize);
			runAction(bounce);
			setNormalImage(getDefaultSprite());

			//gross
			auto scene = CCDirector::sharedDirector()->getRunningScene();
			if (scene->getChildByTag(MENULAYER_TAG) == nullptr) {
				auto layer = reinterpret_cast<CCLayer*>(scene->getChildren()->objectAtIndex(0));
				layer->setKeyboardEnabled(true);
			}
				
		}

		void LoadingButton::activate() {
			m_pNormalImage->stopAllActions();
			m_pNormalImage->setPosition({ 0,51 });
			stopAllActions();
			runAction(CCScaleTo::create(0.0f, 1.0));
			setNormalImage(getDefaultSprite());
			//gross
			auto scene = CCDirector::sharedDirector()->getRunningScene();
			if(scene->getChildByTag(MENULAYER_TAG) == nullptr) 
				CCMenuItemSprite::activate();
		}

		void LoadingButton::invokeLoader(cocos2d::CCObject* extra){
			LoaderProtocol::getLoaderContext()->invokeLoader();
		}
		
		LoadingButton* LoadingButton::create(CCObject* target){
			CCSprite* sprite = getDefaultSprite();
			LoadingButton* obj = new LoadingButton;
			if (obj == nullptr || !obj->initWithNormalSprite(
				sprite, sprite, sprite, 
				obj, 
				menu_selector(LoadingButton::invokeLoader))) {
				CC_SAFE_DELETE(obj);
				return nullptr;
			}
			obj->setSizeMult(1.25);
			obj->autorelease();
			return obj;
		}

	}
}