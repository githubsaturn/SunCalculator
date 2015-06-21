#pragma once
#include "cocos2d.h"
#include "AppConstants.h"

USING_NS_CC;

class SliderControl: public cocos2d::Node {
public:

	static SliderControl* create();


private:
	void setupSlider();


};
