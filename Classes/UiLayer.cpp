#include "UiLayer.h"
#include "CommonMacro.h"
#include "util.h"
#include "StarsHelper.h"
#include "StarColorPanel.h"
#include "EditorModel.h"
#include "ListSlideView.h"
USING_NS_CC;
using namespace std;

bool UiLayer::init()
{
	initPanel();
	return true;
}

void UiLayer::initPanel()
{
	auto winSize = CCDirector::sharedDirector()->getWinSize();
	setContentSize(winSize);

	CCMenu* pMenu = CCMenu::create();
	pMenu->setPosition(ccp(0, 0));
	this->addChild(pMenu, 1);

	float xPos = winSize.width * 0.93f;
	float yPos = winSize.height * 0.93f;
	CCMenuItemSprite *iter = NULL;
	string typeName[10] = { "Empty", "Star", "BounceBall", "DeadVine", "LiveVine", "Stone", "Bomb", "Iron", "Diamond", "Key" };
	for (int i = 0; i < 10; ++i)
	{
		m_menuItemData[i] = i;
		auto item = getBtnWithLabel(typeName[i].c_str());
		item->setTarget(this, menu_selector(UiLayer::onStarTypeBtnClicked));
		item->setPosition(xPos, yPos);
		item->setUserData(&m_menuItemData[i]);
		pMenu->addChild(item);
		yPos -= winSize.height * 0.1f;
	}
	auto openBtn = getBtnWithLabel("open");
	openBtn->setTarget(this, menu_selector(UiLayer::onOpenBtnClicked));
	openBtn->setPosition(ccp(winSize.width * 0.8f, winSize.height * 0.93f));
	pMenu->addChild(openBtn);

	auto saveBtn = getBtnWithLabel("save");
	saveBtn->setTarget(this, menu_selector(UiLayer::onSaveBtnClicked));
	saveBtn->setPosition(ccp(winSize.width * 0.8f, winSize.height * 0.83f));
	pMenu->addChild(saveBtn);


	ListSlideView *listView = ListSlideView::create(CCSize(70, 300));
	listView->setSpacing(10);
	for (int i = 0; i < 10; ++i)
	{
		//auto mask = getMask(CCSize(60, 20));
		auto mask = CCSprite::create("stars/yxjm_fangkuai5.png");
		listView->addNode(mask);
	}
	addChild(listView);
	listView->setAnchorPoint(ccp(0, 1));
	listView->setPositionY(winSize.height * 0.9f);
}

void UiLayer::onStarTypeBtnClicked(cocos2d::CCObject* pSender)
{
	CCNode *node = (CCNode *)pSender;
	int type = *(int *)((node)->getUserData());
	auto config = StarsHelper::theHelper()->getStarConfig(type);
	if (config.hasColor)
	{
		auto panel = StarColorPanel::create();
		panel->setHandle([=](int color)
		{
			EditorModel::theModel()->setCurStar(type, color);
		});
		addChild(panel);
		panel->setAnchorPoint(ccp(1, 0.5f));
		auto pos = node->getPosition();
		auto size = node->getContentSize();
		panel->setPosition(ccp(pos.x - size.width * 0.5f, pos.y));
	}
	else
	{
		EditorModel::theModel()->setCurStar(type, kColorRandom);
	}
}

void UiLayer::onOpenBtnClicked(cocos2d::CCObject* pSender)
{
	EditorModel::theModel()->openNewStage("stage1_stars");
}

void UiLayer::onSaveBtnClicked(cocos2d::CCObject* pSender)
{
	EditorModel::theModel()->save();
}