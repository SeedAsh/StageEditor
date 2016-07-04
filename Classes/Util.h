#ifndef __UTIL_H__
#define __UTIL_H__
#include "cocos2d.h"
cocos2d::CCMenuItemSprite *getBtnWithLabel(const char* str);
const char *intToStr(int value);
cocos2d::CCNode* getMask(const cocos2d::CCSize &size, cocos2d::ccColor4B color = cocos2d::ccc4(255, 0, 0, 145));
std::vector<int> parseStrToInts(std::string str);
std::string parseIntsToStr(const std::vector<int> &values);

#endif