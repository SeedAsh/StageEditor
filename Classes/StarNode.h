#ifndef __STARNODE_H__
#define __STARNODE_H__
#include "cocos2d.h"
#include "TouchNode.h"

struct StarAttr
{
	int starType;
	int color;
};

class StarNode
	: public TouchNode
{
public:
	static StarNode *create(const StarAttr &attr);
	virtual bool init();
	void setStarAttr(int starType, int color);
	const StarAttr &getStarAttr(){ return m_attr; }
private:
	StarNode(const StarAttr &attr): m_attr(attr){}
	virtual bool onTouchBegan(cocos2d::CCPoint pt, bool isInside);
	void refresh();

private:
	StarAttr m_attr;
	cocos2d::CCNode *m_node;
};
#endif