#ifndef __STARCOLORPANEL_H__
#define __STARCOLORPANEL_H__
#include "cocos2d.h"
#include "TouchNode.h"

class StarColorNode
	: public TouchNode
{
public:
	static StarColorNode *create(int color);
private:
	StarColorNode(int color) : m_color(color){}
	virtual bool init();
	virtual bool onTouchBegan(cocos2d::CCPoint pt, bool isInside);
private:
	int m_color;
};

class StarColorPanel
	: public cocos2d::CCNode
	, public cocos2d::CCTouchDelegate
{
public:
	CREATE_FUNC(StarColorPanel);
	void setHandle(std::function<void(int)>handle = NULL){ m_handle = handle; };
	void finishColorSelect(int color);
	void cancelColorSelect();
private:
	virtual bool init();
	virtual void onEnter();
	virtual void onExit();
	virtual bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
private:
	std::function<void(int)> m_handle;
};

#endif