#include "StarsLayer.h"
#include "CommonMacro.h"
#include "StarNode.h"
#include "EditorModel.h"
#include "StarsHelper.h"
#include "SqliteHelper.h"
USING_NS_CC;
using namespace std;

void StarsLayer::onEnter()
{
	CCNode::onEnter();
	EditorModel::theModel()->addView(this);
}

void StarsLayer::onExit()
{
	CCNode::onExit();
	EditorModel::theModel()->removeView(this);
}

bool StarsLayer::init()
{
	return true;
}

void StarsLayer::onOpenNewStage()
{
	removeAllChildren();
	m_starNodes.clear();

	auto tbName = EditorModel::theModel()->getCurTableName();
	if (tbName.empty()) return;

	vector<vector<StageStarInfo>> stars;
	StarsHelper::theHelper()->getStagesData(stars, tbName);
	
	static const float kSpacing = 2;
	float curX = kSpacing;
	float curY = kSpacing;
	float maxHeight = 0;

	for (int row = ROWS_SIZE - 1; row >= 0; --row)
	{
		for (int col = 0; col < COlUMNS_SIZE; ++col)
		{
			auto data = stars[row][col];
			StarAttr attr;
			attr.starType = data.starType;
			attr.color = data.color;
			auto node = StarNode::create(attr);

			node->setAnchorPoint(ccp(0, 0));
			auto size = node->getContentSize();
			node->setPosition(ccp(curX, curY));
			addChild(node);

			m_starNodes.push_back(node);

			curX += size.width + kSpacing;
			if (maxHeight < size.height)
			{
				maxHeight = size.height;
			}
		}
		curX = kSpacing;
		curY += maxHeight + kSpacing;
	}
}

void StarsLayer::onSave()
{
	auto tbName = EditorModel::theModel()->getCurTableName();
	if (tbName.empty()) return;

	char str[100] = { 0 };
	SqliteHelper helper(DB_STAGES);
	string sql;

	helper.clearTable(tbName.c_str());
	helper.openTransaction(true);

	for (int row = ROWS_SIZE - 1; row >= 0; --row)
	{
		sql = "insert into ";
		sql += tbName.c_str();
		sql += " values(";
		for (int col = 0; col < COlUMNS_SIZE; ++col)
		{
			auto data = m_starNodes[ROWS_SIZE * row + col]->getStarAttr();
			char str[100] = { 0 };
			sprintf(str, "\"%d, %d\"", data.starType, data.color);
			sql += str;
			if (col < COlUMNS_SIZE - 1)
			{
				sql += ",";
			}
		}
		sql += ");";
		helper.executeSql(sql.c_str());
	}

	helper.openTransaction(false);

}