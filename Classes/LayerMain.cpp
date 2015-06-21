#include "AppManager.h"
#include "AppConstants.h"
#include "LayerMain.h"
#include "SliderControl.h"

USING_NS_CC;
LayerMain *LayerMain::pInstance = NULL;

// on "init" you need to initialize your instance
bool LayerMain::init() {
	//////////////////////////////
	// 1. super init first
	if (!Layer::init()) {
		return false;
	}

	pInstance = this;

	Size visibleSize = AppManager::getInstance()->getVisibleSize();
	Point origin = AppManager::getInstance()->getOrigin();
	float w = visibleSize.width;
	float h = visibleSize.height;

	Sprite* bg = Sprite::create("white_bg.png");
	bg->setPosition(visibleSize * 0.5);
	bg->setScale(w / bg->getContentSize().width,
			h / bg->getContentSize().height);
	this->addChild(bg, 0);
	bg->setColor(Color3B(240, 240, 240));

	Sprite* countries = Sprite::create("countries.png");
	countries->setAnchorPoint(Vec2(-0.1, 1.2));
	countries->setPosition(0, h);
	countries->setScale(h * 0.4 / countries->getContentSize().height);
	countries->setOpacity(75);
	this->addChild(countries, 1);

	float sideGap = w * 0.03f;
	float thickness = w * 0.01f;

	SliderControl * azSlider = SliderControl::create(Size(w * 0.8, thickness));
	azSlider->setPosition(w * 0.5, sideGap);
	this->addChild(azSlider, 10);

	SliderControl * latSlider = SliderControl::create(Size(h * 0.9, thickness));
	latSlider->setRotation(90);
	latSlider->setPosition(sideGap, h * 0.5);
	this->addChild(latSlider, 20);

	SliderControl * dateSlider = SliderControl::create(
			Size(w * 0.8, thickness));
	dateSlider->setPosition(w * 0.5, h - sideGap);
	this->addChild(dateSlider, 30);

	SliderControl * timeSlider = SliderControl::create(
			Size(h * 0.9, thickness));
	timeSlider->setRotation(90);
	timeSlider->setPosition(w - sideGap, h * 0.5);
	this->addChild(timeSlider, 40);

	auto listenerKeys = EventListenerKeyboard::create();
	listenerKeys->onKeyReleased = CC_CALLBACK_2(LayerMain::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listenerKeys,
			this);

	return true;

}

void LayerMain::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event) {
	log("Key with keycode %d released", keyCode);
	if (keyCode == EventKeyboard::KeyCode::KEY_ESCAPE) {
		Director::getInstance()->end();
	}
}

