#ifndef __UILAYER_H__
#define __UILAYER_H__
#include "cocos2d.h"

class ListSlideView;

class UiLayer
	: public cocos2d::CCNode
{
public:
	CREATE_FUNC(UiLayer);
	virtual bool init();
private:
	void initPanel();
	void initBtns();
	void initList();
	void onStarTypeBtnClicked(cocos2d::CCObject* pSender);
	void onOpenBtnClicked(cocos2d::CCObject* pSender);
	void onSaveBtnClicked(cocos2d::CCObject* pSender);
private:
	cocos2d::CCLabelTTF *m_title;
	int m_menuItemData[10];
	ListSlideView *m_listView;
};
#endif