#include "UiLayer.h"
#include "CommonMacro.h"
#include "util.h"
#include "StarsHelper.h"
#include "StarColorPanel.h"
#include "EditorModel.h"
#include "ListSlideView.h"
#include "FileListNode.h"
USING_NS_CC;
using namespace std;

bool UiLayer::init()
{
	initPanel();
	initBtns();
	initList();
	return true;
}

void UiLayer::initPanel()
{
	auto winSize = CCDirector::sharedDirector()->getWinSize();
	m_title = CCLabelTTF::create("Table Name", "Arial", 40);
	addChild(m_title);
	m_title->setPosition(ccp(winSize.width * 0.5f, winSize.height * 0.95f));
	setContentSize(winSize);
}

void UiLayer::initBtns()
{
	auto winSize = CCDirector::sharedDirector()->getWinSize();
	setContentSize(winSize);

	CCMenu* pMenu = CCMenu::create();
	pMenu->setPosition(ccp(0, 0));
	this->addChild(pMenu);

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
	openBtn->setPosition(ccp(winSize.width * 0.1f, winSize.height * 0.93f));
	pMenu->addChild(openBtn);

	auto saveBtn = getBtnWithLabel("save");
	saveBtn->setTarget(this, menu_selector(UiLayer::onSaveBtnClicked));
	saveBtn->setPosition(ccp(winSize.width * 0.1f, winSize.height * 0.83f));
	pMenu->addChild(saveBtn);
}

void UiLayer::initList()
{
	CCSize listSize = CCSize(200, 450);
	auto winSize = CCDirector::sharedDirector()->getWinSize();
	CCPoint pos = ccp(winSize.width * 0.01f, winSize.height * 0.7f);

	CCSprite *pad = CCSprite::create("ui/pad.png");
	CCSize sprSize = pad->getContentSize();
	pad->setScaleX(listSize.width / sprSize.width);
	pad->setScaleY(listSize.height / sprSize.height);
	pad->setAnchorPoint(ccp(0, 1));
	pad->setPosition(pos);
	addChild(pad);

	m_listView = ListSlideView::create(listSize);
	m_listView->setTouchHanedle([=](int index)
	{
		for (int i = 0; i < m_listView->count(); ++i)
		{
			auto listNode = dynamic_cast<FileListNode *>(m_listView->getNode(i));
			listNode->setBkVisible(false);
		}
		auto listNode = dynamic_cast<FileListNode *>(m_listView->getNode(index));
		listNode->setBkVisible(true);
	});
	m_listView->setSpacing(3);
	auto tbNames = StarsHelper::theHelper()->getStagesFileNames();
	for (int i = 0; i < tbNames.size(); ++i)
	{
		FileListNode *node = FileListNode::create(tbNames[i].c_str());
		m_listView->addNode(node);
	}
	addChild(m_listView);
	m_listView->setAnchorPoint(ccp(0, 1));
	m_listView->setPosition(pos);
}

void UiLayer::onStarTypeBtnClicked(cocos2d::CCObject* pSender)
{
	CCNode *node = (CCNode *)pSender;
	int type = *(int *)((node)->getUserData());
	auto config = StarsHelper::theHelper()->getStarConfig(type);
	if (config.hasColor)
	{
		auto panel = StarColorPanel::create(type);
		panel->setHandle([=](int color)
		{
			EditorModel::theModel()->setCurStar(type, color);
		});
		addChild(panel);
		panel->setAnchorPoint(ccp(1, 0.5f));
		auto pos = node->getPosition();
		auto size = node->getContentSize();
		panel->setPosition(ccp(pos.x - size.width * 0.5f, pos.y));
		panel->showMask();
	}
	else
	{
		EditorModel::theModel()->setCurStar(type, kColorRandom);
	}
}

void UiLayer::onOpenBtnClicked(cocos2d::CCObject* pSender)
{
	int curIndex = m_listView->getCurNodeIndex();
	auto listNode = dynamic_cast<FileListNode *>(m_listView->getNode(curIndex));
	if (listNode)
	{
		auto tbName = listNode->getFileName();
		EditorModel::theModel()->openNewStage(tbName);
		m_title->setString(tbName.c_str());
	}
}

void UiLayer::onSaveBtnClicked(cocos2d::CCObject* pSender)
{
	EditorModel::theModel()->save();
}