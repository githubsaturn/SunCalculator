#pragma once

#include <stdio.h>
#include "cocos2d.h"

using namespace cocos2d;

class LayerSplash: public cocos2d::Layer {
public:

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();


	// implement the "static create()" method manually
	CREATE_FUNC(LayerSplash)
	;


private:
	void runMainScene(float dt);

};

