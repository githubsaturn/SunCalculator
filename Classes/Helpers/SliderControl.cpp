#include "SliderControl.h"
#include "cocos2d.h"

USING_NS_CC;

// Static members initialization - necessary.
// Static members: none

SliderControl* SliderControl::create() {

	SliderControl *sprite = new (std::nothrow) SliderControl();

	if (sprite && sprite->init()) {

		sprite->autorelease();
		sprite->setupSlider();

		return sprite;
	}

	CC_SAFE_DELETE(sprite);
	return nullptr;
}

void SliderControl::setupSlider() {

	Sprite* bar = Sprite::create("sliderbar.png");
	this->addChild(bar);

}

