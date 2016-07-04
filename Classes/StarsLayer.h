#ifndef __STARSLAYER_H__
#define __STARSLAYER_H__
#include "cocos2d.h"
#include "EditorModel.h"

class UiLayout;
class StarNode;

class StarsLayer
	: public cocos2d::CCNode
	, public IEditorView
{
public:
	CREATE_FUNC(StarsLayer);
	virtual bool init();
private:
	virtual void onEnter();
	virtual void onExit();
private:
	virtual void onOpenNewStage();
	virtual void onSave();
private:
	UiLayout *m_layout;
	std::vector<StarNode *> m_starNodes;
};
#endif