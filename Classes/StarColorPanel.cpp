#include "StarColorPanel.h"
#include "StarsHelper.h"
#include "CommonMacro.h"
#include "util.h"
USING_NS_CC;
using namespace std;

static int kStarsColorPanelTouchPrority = -130;

StarColorNode *StarColorNode::create(int type, int color)
{
	StarColorNode *node = new StarColorNode(type, color);
	node->init();
	node->autorelease();
	return node;
}

bool StarColorNode::init()
{
	auto spr = StarsHelper::theHelper()->getStarsSpr(m_type, m_color);
	auto size = spr->getContentSize();
	addChild(spr);
	setContentSize(size);
	setTouchPriority(kStarsColorPanelTouchPrority - 1);
	return true;
}

bool StarColorNode::onTouchBegan(cocos2d::CCPoint pt, bool isInside)
{
	auto parent = (StarColorPanel *)getParent();
	if (isInside)
	{
		parent->finishColorSelect(m_color);
	}
	else
	{
		parent->cancelColorSelect();
	}
	return isInside;
}

////////////////////////////////////////////////////////////
StarColorPanel *StarColorPanel::create(int type)
{
	StarColorPanel *node = new StarColorPanel(type);
	node->init();
	node->autorelease();
	return node;
}

void StarColorPanel::onEnter()
{
	CCNode::onEnter();
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, kStarsColorPanelTouchPrority, true);
}

void StarColorPanel::onExit()
{
	CCNode::onExit();
	CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
}

bool StarColorPanel::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
	return true;
}

bool StarColorPanel::init()
{
	CCSize curSize(0, 0);
	static const float kSpacing = 10;
	for (int color = kColorRandom; color <= kColorPurple; ++color)
	{
		auto node = StarColorNode::create(m_type, color);
		auto size = node->getContentSize();
		addChild(node);
		node->setPosition(curSize.width, 0);
		curSize.width += size.width + kSpacing;
		curSize.height = max(curSize.height, size.height);
	}

	setContentSize(curSize);
	return true;
}

void StarColorPanel::showMask()
{
	auto winSize = CCDirector::sharedDirector()->getWinSize();
	auto size = getContentSize();
	auto mask = getMask(winSize, ccc4(0, 0, 0, 165));
	CCPoint pos;
	pos.x = size.width - getPositionX();
	pos.y = size.height * 0.5f - getPositionY();
	mask->setPosition(pos);
	addChild(mask, -1);
}

void StarColorPanel::finishColorSelect(int color)
{
	if (m_handle)
	{
		m_handle(color);
	}
	removeFromParent();
}

void StarColorPanel::cancelColorSelect()
{
	removeFromParent();
}
