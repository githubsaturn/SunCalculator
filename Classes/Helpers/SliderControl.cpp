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
	hub->setScale(s.height * 2.5 / hub->getContentSize().height);

	this->addChild(bar, 10);
	this->addChild(hub, 20);
	bar->setColor(color);
	hub->setColor(Color3B(color.r * 0.5, color.g * 0.5, color.b * 0.5));

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

	if ((abs(newX) < size.width * 0.5) && (abs(newY) < size.height * 4))
		listener->setSwallowTouches(true);

	return true;
}

void SliderControl::onTouchMoved(Touch *touch, Event *unused_event) {
	//cocos2d::log("I am onTouchMoved");

	if (touch->getID() != 0)
		return;

	if (!listener->isSwallowTouches())
		return;

	float newX = this->convertTouchToNodeSpace(touch).x;

	if (abs(newX) <= xLimit)
		hub->setPositionX(newX);
}

void SliderControl::onTouchEnded(Touch *touch, Event *unused_event) {
	// cocos2d::log("I am onTouchEnded");

	if (touch->getID() != 0)
		return;

	listener->setSwallowTouches(false);

}

