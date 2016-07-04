#ifndef __STARSHELPER_H__
#define __STARSHELPER_H__
#include "cocos2d.h"
struct StarsConfig
{
	int id;
	std::string randomColor;
	std::string red;
	std::string yellow;
	std::string blue;
	std::string green;
	std::string purple;
	std::string extra;
	bool hasColor;
};

struct StageStarInfo
{
	int starType;
	int color;
};

class StarsHelper
{
public:
	static StarsHelper *theHelper();
	StarsConfig getStarConfig(int type);
	cocos2d::CCNode *getStarsSpr(int starsType, int color);
	void loadStarsConfig();

	void getStagesData(std::vector<std::vector<StageStarInfo>> &stars, const std::string &tableName);
	void saveCurStageData();

private:
private:
	std::vector<StarsConfig> m_starsConfig;
};
#endif