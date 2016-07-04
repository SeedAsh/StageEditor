#include "EditorModel.h"
#include "SqliteHelper.h"
#include "StarsHelper.h"
#include "CommonMacro.h"
using namespace std;

EditorModel *EditorModel::theModel()
{
	static EditorModel model;
	return &model;
}

void EditorModel::init()
{
	StarsHelper::theHelper()->loadStarsConfig();
}

void EditorModel::setCurStar(int starType, int color)
{
	m_starState.starType = starType;
	m_starState.color = color;
}

void EditorModel::addView(IEditorView *view)
{
	auto iter = find(m_views.begin(), m_views.end(), view);
	if (iter == m_views.end())
	{
		m_views.push_back(view);
	}
}

void EditorModel::removeView(IEditorView *view)
{
	auto iter = find(m_views.begin(), m_views.end(), view);
	if (iter != m_views.end())
	{
		m_views.erase(iter);
	}
}

void EditorModel::openNewStage(string tableName)
{
	m_curTabelName = tableName;
	NOTIFY_VIEWS(onOpenNewStage);
}

void EditorModel::save()
{
	NOTIFY_VIEWS(onSave);
}
