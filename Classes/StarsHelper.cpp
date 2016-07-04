#include "StarsHelper.h"
#include "SqliteHelper.h"
#include "CommonMacro.h"
#include "util.h"
using namespace std;
USING_NS_CC;

StarsHelper *StarsHelper::theHelper()
{
	static StarsHelper helper;
	return &helper;
}

void StarsHelper::loadStarsConfig()
{
	SqliteHelper helper(DB_STAGE_EDITOR);
	auto result = helper.readRecord("select * from stars");
	for (size_t i = 0; i < result.size(); ++i)
	{
		auto data = result[i];
		StarsConfig config;
		config.id = atoi(data[0]);
		config.randomColor = data[1];
		config.red = data[2];
		config.yellow = data[3];
		config.blue = data[4];
		config.green = data[5];
		config.purple = data[6];
		config.hasColor = atoi(data[7]) == 1;
		config.extra = data[8];

		m_starsConfig.push_back(config);
	}
}

StarsConfig StarsHelper::getStarConfig(int type)
{
	assert(type >= kEmpty && type <= kKey);
	return m_starsConfig[type];
}

cocos2d::CCNode *StarsHelper::getStarsSpr(int starsType, int color)
{
	auto data = m_starsConfig[starsType];
	CCNode *node = CCNode::create();
	if (data.hasColor)
	{
		string colorRes;
		switch (color)
		{
		case kColorRandom:
			colorRes = data.randomColor;
			break;
		case kColorRed:
			colorRes = data.red;
			break;
		case kColorYellow:
			colorRes = data.yellow;
			break;
		case kColorBlue:
			colorRes = data.blue;
			break;
		case kColorGreen:
			colorRes = data.green;
			break;
		case kColorPurple:
			colorRes = data.purple;
			break;
		default:
			break;
		}
		if (!colorRes.empty())
		{
			CCSprite *colorSpr = CCSprite::create(colorRes.c_str());
			node->addChild(colorSpr);
			auto size = colorSpr->getContentSize();
			colorSpr->setPosition(ccpMult(size, 0.5f));
			node->setContentSize(size);
		}
	}

	if (!data.extra.empty())
	{
		CCSprite *extra = CCSprite::create(data.extra.c_str());
		node->addChild(extra);
		auto size = extra->getContentSize();
		extra->setPosition(ccpMult(size, 0.5f));
		node->setContentSize(size);
	}
	return node;
}



void StarsHelper::getStagesData(std::vector<std::vector<StageStarInfo>> &stars, const std::string &tableName)
{
	SqliteHelper sqlHelper(DB_STAGES);

	char str[100] = { 0 };
	sprintf(str, "select * from %s", tableName.c_str());
	auto result = sqlHelper.readRecord(str);

	assert(result.size() == ROWS_SIZE);
	for (auto iter = result.begin(); iter != result.end(); ++iter)
	{
		assert((*iter).size() == COlUMNS_SIZE);

		vector<StageStarInfo> oneRow;
		for (size_t i = 0; i < (*iter).size(); ++i)
		{
			StageStarInfo info;
			auto data = (*iter)[i];
			auto reInts = parseStrToInts(data);
			info.starType = reInts[0];
			info.color = reInts[1];
			oneRow.push_back(info);
		}
		stars.push_back(oneRow);
	}
}

void StarsHelper::saveCurStageData()
{
	/*
	char str[100] = { 0 };
	SqliteHelper helper(DB_STAGES);
	string sql;

	helper.openTransaction(true);
	for (int row = ROWS_SIZE - 1; row >= 0; --row)
	{
		vector<string> stars;
		sql.clear();
		sql = "update save_stars values("; //只有一条记录 id=1
		for (int col = 0; col < COlUMNS_SIZE; ++col)
		{
			LogicGrid grid(col, row);
			int star = kEmpty;
			auto node = stageModel->getStarNode(grid);
			if (node)
			{
				star = node->getAttr().type;
			}
			sprintf(str, "%d,", star);
			sql += str;
		}
		sql = sql.substr(0, sql.length() - 1); //去掉最后一个逗号
		sql += ");";
		helper.executeSql(sql.c_str());
	}
	helper.openTransaction(false);
	helper.closeDB();
	*/
}

