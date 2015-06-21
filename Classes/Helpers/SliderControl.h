#pragma once
#include "cocos2d.h"
#include "AppConstants.h"

USING_NS_CC;

class SliderControl: public cocos2d::Node {
public:

	static SliderControl* create(Size s, float maxAndMin = 1.0f, Color3B c =
			Color3B::GREEN);
	float getValue();

private:
	void setupSlider();

	bool onTouchBegan(Touch *touch, Event *unused_event);
	void onTouchMoved(Touch *touch, Event *unused_event);
	void onTouchEnded(Touch *touch, Event *unused_event);

	Size size;
	float maxAndMin;
	EventListenerTouchOneByOne* listener;
	Sprite* hub;
	float xLimit;
	float hubScale;
	Color3B color;

};
