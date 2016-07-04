#ifndef __UILAYER_H__
#define __UILAYER_H__
#include "cocos2d.h"

class UiLayer
	: public cocos2d::CCNode
{
public:
	CREATE_FUNC(UiLayer);
	virtual bool init();
private:
	void initPanel();
	void onStarTypeBtnClicked(cocos2d::CCObject* pSender);
	void onOpenBtnClicked(cocos2d::CCObject* pSender);
	void onSaveBtnClicked(cocos2d::CCObject* pSender);
	int m_menuItemData[10];
};
#endif