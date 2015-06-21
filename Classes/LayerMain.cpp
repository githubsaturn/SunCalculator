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

	float scalingHeight = visibleSize.height;
	if (scalingHeight > (w * 0.5))
		scalingHeight = w * 0.5;

	Sprite* bg = Sprite::create("white_bg.png");
	bg->setPosition(visibleSize * 0.5);
	bg->setScale(w / bg->getContentSize().width,
			h / bg->getContentSize().height);
	this->addChild(bg, 0);
	bg->setColor(Color3B(244, 244, 244));

	Sprite* countries = Sprite::create("countries_.png");
	countries->setAnchorPoint(Vec2(-0.1, 1.2));
	countries->setPosition(0, h);
	countries->setScale(h * 0.4 / countries->getContentSize().height);
	countries->setOpacity(73);
	this->addChild(countries, 1);

	Sprite* star = Sprite::create("star.png");
	star->setPosition(countries->getContentSize() * 0.5);
	star->setScale(
			countries->getContentSize().height * 0.05
					/ star->getContentSize().height);
	countries->addChild(star, 1);

	Sprite* platform = Sprite::create("platform.png");
	platform->setAnchorPoint(Vec2(1.5, 1.3));
	platform->setPosition(w, h);
	platform->setScale(h * 0.4 / platform->getContentSize().height);
	this->addChild(platform, 1);

	Sprite* shadow = Sprite::create("shadow.png");
	shadow->setAnchorPoint(Vec2(0.0, 0.5));
	shadow->setScaleX(
			platform->getContentSize().width * 0.5
					/ shadow->getContentSize().width);
	shadow->setPosition(platform->getContentSize() * 0.5);
	shadow->runAction(RotateBy::create(30, 3600));
	platform->addChild(shadow, 1);

	Sprite* sun = Sprite::create("sun.png");
	float sunDist = platform->getContentSize().height * 0.5;
	sun->setPosition(0, sunDist);
	sun->runAction(RotateBy::create(90, 3600));
	platform->addChild(sun, 10);

	Sprite* object = Sprite::create("object.png");
	object->setAnchorPoint(Vec2(0.5, 0.3));
	object->setPosition(platform->getContentSize() * 0.5);
	platform->addChild(object, 10);

	float sideGap = w * 0.03f;
	float thickness = w * 0.007f;

	SliderControl * azSlider = SliderControl::create(Size(w * 0.8, thickness),
			180, Color3B(255, 32, 32));
	azSlider->setPosition(w * 0.5, sideGap);
	this->addChild(azSlider, 10);

	SliderControl * latSlider = SliderControl::create(Size(h * 0.9, thickness),
			90, Color3B(22, 196, 52));
	latSlider->setRotation(90);
	latSlider->setPosition(sideGap, h * 0.5);
	this->addChild(latSlider, 20);

	SliderControl * dateSlider = SliderControl::create(Size(w * 0.8, thickness),
			1, Color3B(239, 32, 155));
	dateSlider->setPosition(w * 0.5, h - sideGap);
	this->addChild(dateSlider, 30);

	SliderControl * timeSlider = SliderControl::create(Size(h * 0.9, thickness),
			1, Color3B(22, 131, 196));
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

