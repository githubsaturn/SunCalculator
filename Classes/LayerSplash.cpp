#include "AppManager.h"
#include "AppConstants.h"
#include "LayerSplash.h"

USING_NS_CC;

// on "init" you need to initialize your instance
bool LayerSplash::init() {
	//////////////////////////////
	// 1. super init first
	if (!Layer::init()) {
		return false;
	}

	this->scheduleOnce(CC_SCHEDULE_SELECTOR(LayerSplash::runMainScene), 3.0f);

	Sprite* bg = Sprite::create("splash_bg.png");
	bg->setScale(
			AppManager::getInstance()->getVisibleSize().width
					/ bg->getContentSize().width,
			AppManager::getInstance()->getVisibleSize().height
					/ bg->getContentSize().height);
	bg->setAnchorPoint(Vec2::ZERO);

	Sprite* logo = Sprite::create("splash_logo.png");
	logo->setScale(
			AppManager::getInstance()->getVisibleSize().height * 0.6
					/ logo->getContentSize().height);
	logo->setPosition(AppManager::getInstance()->getVisibleSize() * 0.5f);

	this->addChild(bg, 0);
	this->addChild(logo, 0);

	return true;

}

void LayerSplash::runMainScene(float dt) {
	AppManager::getInstance()->runScene(kSceneMain);
}
