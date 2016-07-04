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

std::vector<std::string> StarsHelper::getStagesFileNames()
{
	SqliteHelper sqlHelper(DB_STAGES);

	auto data = sqlHelper.getDBInfo();
	vector<string> tbNames;
	for (auto iter = data.begin(); iter != data.end(); ++iter)
	{
		tbNames.push_back(iter->first);
	}
	return tbNames;
}
