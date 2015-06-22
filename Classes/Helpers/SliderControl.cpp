#include "SliderControl.h"
#include "cocos2d.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

// Static members initialization - necessary.
// Static members: none

SliderControl* SliderControl::create(Size s, float maxAndMin, Color3B c) {

	SliderControl *sprite = new (std::nothrow) SliderControl();

	if (sprite && sprite->init()) {

		sprite->autorelease();
		sprite->size = s;
		sprite->color = c;
		sprite->maxAndMin = maxAndMin;
		sprite->setupSlider();

		return sprite;
	}

	CC_SAFE_DELETE(sprite);
	return nullptr;
}

void SliderControl::setupSlider() {

	Size s = size;
	Node* bar = ui::Scale9Sprite::create("sliderbar.png");

	float k = s.height / bar->getContentSize().height;
	float l0 = k * bar->getContentSize().width;
	float w0 = s.width / l0;

	float a = bar->getContentSize().width;
	float b = bar->getContentSize().height;

	bar->setContentSize(Size(a * w0, b));
	bar->setScale(k);

	hub = Sprite::create("sliderhub.png");
	Sprite* hubCore = Sprite::create("sliderhub.png");
	hubCore->setPosition(hub->getContentSize() * 0.5);
	hubCore->setScale(0.7);
	hub->addChild(hubCore);
	hubScale = s.height * 3.5 / hub->getContentSize().height;
	hub->setScale(hubScale);

	this->addChild(bar, 10);
	this->addChild(hub, 20);
	bar->setColor(Color3B(160, 160, 160));
	hub->setColor(color);

	xLimit = size.width * 0.5 - size.height * 1.5;

	// Touch listeners preparation:
	listener = EventListenerTouchOneByOne::create();
	// if swallow true - it does not pass on to the children
	listener->setSwallowTouches(false);
	listener->onTouchBegan = CC_CALLBACK_2(SliderControl::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(SliderControl::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(SliderControl::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

}

float SliderControl::getValue() {
	return (maxAndMin * hub->getPositionX() / xLimit);
}

bool SliderControl::onTouchBegan(Touch *touch, Event *unused_event) {
	// cocos2d::log("I am onTouchBegan");

	if (touch->getID() != 0)
		return false;

	float newX = this->convertTouchToNodeSpace(touch).x;
	float newY = this->convertTouchToNodeSpace(touch).y;

	if ((abs(newX) < size.width * 0.5) && (abs(newY) < size.height * 4)) {
		listener->setSwallowTouches(true);
		hub->stopAllActions();
		hub->runAction(
				EaseSineOut::create(ScaleTo::create(0.2f, hubScale * 1.7)));
	}

	return true;
}

void SliderControl::onTouchMoved(Touch *touch, Event *unused_event) {
	//cocos2d::log("I am onTouchMoved");

	if (touch->getID() != 0)
		return;

	if (!listener->isSwallowTouches())
		return;

	float newX = this->convertTouchToNodeSpace(touch).x;

	if (newX > xLimit) {
		newX = xLimit;
	} else if (newX < -xLimit) {
		newX = -xLimit;
	}

	hub->setPositionX(newX);

}

void SliderControl::onTouchEnded(Touch *touch, Event *unused_event) {
	// cocos2d::log("I am onTouchEnded");

	if (touch->getID() != 0)
		return;

	listener->setSwallowTouches(false);
	hub->stopAllActions();
	hub->runAction(EaseSineOut::create(ScaleTo::create(0.2f, hubScale)));

}

