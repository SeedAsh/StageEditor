#include "MainScene.h"
#include "CommonMacro.h"
#include "StarsLayer.h"
#include "UiLayer.h"

USING_NS_CC;

CCScene* MainScene::scene()
{
    CCScene *scene = CCScene::create();
    MainScene *layer = MainScene::create();
    scene->addChild(layer);
    return scene;
}

bool MainScene::init()
{
    if ( !CCLayer::init() )
    {
        return false;
    }
    
	CCLayerColor *bg = CCLayerColor::create(ccc4(60, 60, 60, 255));
	addChild(bg);

	auto winSize = CCDirector::sharedDirector()->getWinSize();
	auto starsLayer = StarsLayer::create();
	starsLayer->setPosition(ccp(winSize.width * 0.3f, winSize.height * 0.1f));
	addChild(starsLayer);

	auto uiLayer = UiLayer::create();
	addChild(uiLayer);

    return true;
}
