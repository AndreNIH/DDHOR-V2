#include "ListWidget.h"
#define FTS_FUZZY_MATCH_IMPLEMENTATION
#include <fts/fuzzymatch.h>
using namespace cocos2d;

bool ListItem::initListItem(const std::string& label, const cocos2d::CCSize& size, CCObject* target, SEL_MenuHandler selector) {
    CCMenuItem::initWithTarget(target, selector);
    
    m_bg = extension::CCScale9Sprite::create("square02_small_white.png");
    m_bg->setContentSize(size);
    m_bg->setAnchorPoint({ 0,0 });

    
    m_label = CCLabelBMFont::create(label.c_str(), "chatFont.fnt");
    m_label->setScale(0.5);
    m_label->setColor(ccBLACK);
    m_label->setAlignment(CCTextAlignment::kCCTextAlignmentCenter);
    auto ap = m_label->getAnchorPoint();
    m_label->setAnchorPoint({ ap.x,-0.5 });
    m_label->setPositionX(size.width / 2);

    setContentSize(size);
    addChild(m_bg);
    addChild(m_label);
    return true;
}

ListItem* ListItem::create(const std::string& label, const CCSize& size)
{
    return create(label, size, nullptr, nullptr);
}

ListItem* ListItem::create(const std::string& label, const cocos2d::CCSize& size, cocos2d::CCObject* target, SEL_MenuHandler selector)
{
    auto pRet = new ListItem();
    pRet->initListItem(label, size,target,selector);
    pRet->autorelease();
    return pRet;
}

//===================================================

bool DropdownList::matchesFilter(const std::string& item) const{
    bool match = fts::fuzzy_match_simple(m_filter.c_str(), item.c_str());
    return m_filter.empty() || (match && item != m_filter);
}

std::optional<std::vector<std::string>> DropdownList::getDisplayableItems() const{
    std::vector<std::string>filteredItems;
    for (auto& it : m_listItems) {
        if (it == m_filter) return std::vector<std::string>{};
        if (matchesFilter(it)) {
            filteredItems.push_back(it);
        }
    }
    
    std::vector<std::string>displayable;
    int start = m_maxItemDisplay * m_displayIndex;
    if (start > filteredItems.size()) return std::nullopt;
    int hit = 0;
    for (int i = start; i < filteredItems.size() && (hit < m_maxItemDisplay); i++) {
        displayable.push_back(filteredItems[i]);
        hit++;
    }
    return displayable;
    //V2:
    /*const size_t begIndex = m_maxItemDisplay * m_displayIndex;
    if (begIndex >= m_listItems.size()) return std::nullopt;
    const auto begIter = m_listItems.cbegin() + begIndex;
    const auto discoverable = std::vector<std::string>(begIter, m_listItems.cend());
    std::vector<std::string>displayable;
    int matches = 0;
    for (int i = 0; i < discoverable.size() && matches < m_maxItemDisplay; i++) {
        std::string l = discoverable[i];
        if (matchesFilter(l)) {
            matches++;
            displayable.push_back(l);
        }
    }
    return displayable;*/
    
    //V1:
    /*const auto begIter = m_listItems.cbegin() + begIndex;
    const auto endIter = begIndex + m_maxItemDisplay > m_listItems.size()
        ? m_listItems.cend()
        : begIter + m_maxItemDisplay;

    if (begIndex >= m_listItems.size()) return std::nullopt;
    const auto discoverable = std::vector<std::string>(begIter, endIter);
    
    std::vector<std::string>displayable;
    for (int i = 0; i < discoverable.size(); i++) {
        std::string l = discoverable[i];
        if (matchesFilter(l))
            displayable.push_back(l);
    }*/
}

void DropdownList::itemTouchHandler(CCObject* parent) {
    
    auto item = dynamic_cast<ListItem*>(parent);
    if (!item) throw std::runtime_error{"Item is not ListItem"};
    if (m_delegate) m_delegate->dropdownItemSelected(item);
}

void DropdownList::refreshListDisplay(){
    auto displayable = getDisplayableItems();
    if (!displayable.has_value()) return;
    
    CCMenu::removeAllChildren();
    for (auto item : displayable.value()) {
        auto child = ListItem::create(item, m_unitSize, this, menu_selector(DropdownList::itemTouchHandler));
        CCMenu::addChild(child);
    }
    alignItemsVerticallyWithPadding(m_padding);
}

void DropdownList::addListElement(const std::string& element)
{
    m_listItems.push_back(element);
    refreshListDisplay();
}

void DropdownList::addListElements(const std::vector<std::string>& elements)
{
    for (const auto& e : elements) m_listItems.push_back(e);
    refreshListDisplay();
}

void DropdownList::setDisplayFilter(const std::string& filter){
    m_filter = filter;
    m_displayIndex = 0;
    refreshListDisplay();
}

void DropdownList::setMaxItemDisplay(int displayCount){
    m_maxItemDisplay = displayCount;
    refreshListDisplay();
}

void DropdownList::setDisplayIndex(int index) {
    m_displayIndex = std::clamp(index, 0, m_maxItemDisplay -1);
    refreshListDisplay();

}
void DropdownList::setPadding(double padding) {
    m_padding = padding;
    refreshListDisplay();
}

const CCSize& DropdownList::getContentSize() const
{
    float height = -m_padding;
    if (m_pChildren && m_pChildren->count() > 0) {
        CCObject* pObject = nullptr;
        CCARRAY_FOREACH(m_pChildren, pObject) {
            CCNode* pChild = dynamic_cast<CCNode*>(pObject);
            if (pChild) height += pChild->getContentSize().height * pChild->getScaleY() + m_padding;
        }
    }
    return { m_unitSize.width,height };
}

DropdownList* DropdownList::create(const cocos2d::CCSize& boxSize){
    auto* p = new DropdownList(boxSize);
    if (p && p->init()) {
        p->autorelease();
        return p;
    }
    else {
        CC_SAFE_DELETE(p);
        return nullptr;
    }
}
