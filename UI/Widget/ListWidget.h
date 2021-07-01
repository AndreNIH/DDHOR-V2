#pragma once
#include <vector>
#include <gd.h>
#include <cocos-ext.h>
#include <optional>
//Required, otherwise SEL_MenuHandler wont work
using namespace cocos2d;
class DropdownListDelegate;

class ListItem : public cocos2d::CCMenuItem{
	cocos2d::CCLabelBMFont* m_label          = nullptr;
	cocos2d::extension::CCScale9Sprite* m_bg = nullptr;
	DropdownListDelegate* m_dropdownDelegate = nullptr;
	
	//void onHover();
	//void onClick();

public:
	std::string getText() const {return m_label->getString();}
	bool initListItem(const std::string& label, const cocos2d::CCSize& size, cocos2d::CCObject* target, SEL_MenuHandler selector);
	static ListItem* create(const std::string& label, const cocos2d::CCSize& size);
	static ListItem* create(const std::string& label, const cocos2d::CCSize& size, cocos2d::CCObject* target, SEL_MenuHandler selector);
};

class DropdownList : public cocos2d::CCMenu {
private:
	std::vector<std::string>m_listItems;
	cocos2d::CCSize m_unitSize;
	std::string m_filter;

	int m_maxItemDisplay = 5;
	int m_displayIndex = 0;
	double m_padding = 0;

	bool matchesFilter(const std::string& item) const;
	std::optional<std::vector<std::string>>getDisplayableItems() const;
	void itemTouchHandler(CCObject* parent);

public:
	/*void addChild(cocos2d::CCNode* child) { throw std::runtime_error{METHOD_DISALLOWED}; }
	void addChild(cocos2d::CCNode* child, int zOrder) { throw std::runtime_error{ METHOD_DISALLOWED }; }
	void addChild(cocos2d::CCNode* child, int zOrder, int tag) { throw std::runtime_error{ METHOD_DISALLOWED }; }*/
	
	void refreshListDisplay();
	void addListElement(const std::string& element);
	void addListElements(const std::vector<std::string>& elments);
	void setDisplayFilter(const std::string& filter);
	void setMaxItemDisplay(int displayCount);
	void setDisplayIndex(int index);
	void setPadding(double padding);
	
	int getDisplayIndex() const { return m_displayIndex; }
	CC_SYNTHESIZE_NV(DropdownListDelegate*, m_delegate, ListDelegate);
public:
	const CCSize& getContentSize() const override;
	DropdownList(const cocos2d::CCSize& itemSize) :m_unitSize(itemSize), m_delegate(nullptr) {};

	static DropdownList* create(const cocos2d::CCSize& boxSize);

};

class DropdownListDelegate {
public:
	virtual void dropdownItemSelected(ListItem* item) {}
};