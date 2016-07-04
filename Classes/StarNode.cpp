#include "StarNode.h"
#include "StarsHelper.h"
#include "EditorModel.h"
USING_NS_CC;
using namespace std;

StarNode *StarNode::create(const StarAttr &attr)
{
	StarNode *node = new StarNode(attr);
	node->init();
	node->autorelease();
	return node;
}

bool StarNode::init()
{
	m_node = CCNode::create();
	addChild(m_node);
	refresh();
	return true;
}

bool StarNode::onTouchBegan(cocos2d::CCPoint pt, bool isInside)
{
	if (isInside)
	{
		auto state = EditorModel::theModel()->getCurStarState();
		m_attr.starType = state.starType;
		m_attr.color = state.color;
		refresh();
	}
	return isInside;
}

void StarNode::refresh()
{
	m_node->removeAllChildren();
	auto spr = StarsHelper::theHelper()->getStarsSpr(m_attr.starType, m_attr.color);
	m_node->addChild(spr);
	setContentSize(spr->getContentSize());
}

void StarNode::setStarAttr(int starType, int color)
{
	m_attr.starType = starType;
	m_attr.color = color;

	refresh();
}