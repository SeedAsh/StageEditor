#ifndef __MAINSCENE_H__
#define __MAINSCENE_H__

#include "cocos2d.h"

class MainScene : public cocos2d::CCLayer
{
public:
    virtual bool init();  
    static cocos2d::CCScene* scene();
    CREATE_FUNC(MainScene);
private:
};

#endif // __MainScene_SCENE_H__
