#ifndef __EDITORMODEL_H__
#define __EDITORMODEL_H__
#include "cocos2d.h"
struct IEditorView
{
	virtual void onCurStarChanged(){}
	virtual void onOpenNewStage(){}
	virtual void onSave(){}
};

struct StarState
{
	int starType;
	int color;
};

class EditorModel
{
public:
	static EditorModel *theModel();
	const StarState &getCurStarState(){ return m_starState; }
	void setCurStar(int starType, int color);
	void init();
	void save();

	void openNewStage(std::string tableName);
	std::string getCurTableName(){ return m_curTabelName; }
public:
	void addView(IEditorView *view);
	void removeView(IEditorView *view);
private:
	std::vector<IEditorView *> m_views;
	StarState m_starState;
	std::string m_curTabelName;
};
#endif