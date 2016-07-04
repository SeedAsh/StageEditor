#include "Util.h"
USING_NS_CC;
using namespace std;

static CCNode *getBtnSprite(const char *str)
{
	const char* path = "ui/btn.png";
	CCNode *node = CCNode::create();
	auto spr = CCSprite::create(path);
	auto size = spr->getContentSize();
	spr->setPosition(ccp(size.width * 0.5f, size.height * 0.5f));
	node->addChild(spr);

	CCLabelTTF* pLabel = CCLabelTTF::create(str, "Arial", 24);
	pLabel->setAnchorPoint(ccp(0.5f, 0.5f));
	pLabel->setPosition(ccp(size.width * 0.5f, size.height * 0.5f));
	node->addChild(pLabel);

	node->setContentSize(size);
	return node;
}

CCMenuItemSprite *getBtnWithLabel(const char* str)
{
	CCNode* sItem = getBtnSprite(str);
	CCNode* sSelItem = getBtnSprite(str);
	float scale = 1.1f;
	sSelItem->setScale(scale);
	CCMenuItemSprite* menuItem = CCMenuItemSprite::create(sItem, sSelItem, NULL, NULL);
	sSelItem->setAnchorPoint(ccp((scale - 1.0f) * 0.5f, (scale - 1.0f) * 0.5f));
	return menuItem;
}

const char *intToStr(int value)
{
	static char str[100];
	sprintf(str, "%d", value);
	return str;
}

CCNode* getMask(const CCSize &size, cocos2d::ccColor4B color)
{
	auto mask = CCLayerColor::create(color);
	mask->setContentSize(size);
	return mask;
}

static vector<string> split(string str, string pattern)
{
	string::size_type pos;
	vector<string> result;
	str += pattern;//扩展字符串以方便操作
	int size = str.size();

	for (int i = 0; i < size; i++)
	{
		pos = str.find(pattern, i);
		if (pos < size)
		{
			string s = str.substr(i, pos - i);
			result.push_back(s);
			i = pos + pattern.size() - 1;
		}
	}
	return result;
}

vector<int> parseStrToInts(string str)
{
	vector<int> ints;
	if (!str.empty())
	{
		auto strs = split(str, ",");
		for (size_t i = 0; i < strs.size(); ++i)
		{
			ints.push_back(atoi(strs[i].c_str()));
		}
	}
	return ints;
}

string parseIntsToStr(const vector<int> &values)
{
	string str;
	for (size_t i = 0; i < values.size(); ++i)
	{
		str += intToStr(values[i]);
		if (i < values.size() - 1)
		{
			str += ",";
		}
	}
	return str;
}