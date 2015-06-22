#pragma once

#include <stdio.h>
#include "cocos2d.h"
#include "SliderControl.h"

using namespace cocos2d;

class LayerMain: public cocos2d::Layer {
public:

	~LayerMain() {
		//delete windowButtons;
	}
	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();

	void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);

	// implement the "static create()" method manually
	CREATE_FUNC(LayerMain)
	;

	static LayerMain* pInstance;

private:
	void updateValues(float dt);

	Sprite *sun, *shadow, *star, *countries;
	SliderControl *longSlider, *latSlider, *dateSlider, *timeSlider;

	Label *labelLat, *labelLong, *labelDate, *labelTime, *labelTimeZone,
			*labelAz, *labelElv;
	float sunDist;
	float shadowScale;
	int daysInMonth[12];

};

