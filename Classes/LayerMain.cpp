#include "AppManager.h"
#include "AppConstants.h"
#include "LayerMain.h"

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

	this->schedule(CC_SCHEDULE_SELECTOR(LayerMain::updateValues));

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
	countries->setScale(
			scalingHeight * 0.4 / countries->getContentSize().height);
	countries->setOpacity(73);
	this->addChild(countries, 1);

	star = Sprite::create("star.png");
	star->setPosition(countries->getContentSize() * 0.5);
	star->setScale(
			countries->getContentSize().height * 0.05
					/ star->getContentSize().height);
	countries->addChild(star, 1);

	float fontSize = scalingHeight * 0.06;

	Label* lLoc = Label::createWithTTF("Latitude    Longitude",
			"fonts/trench100free.otf", fontSize);
	lLoc->setTextColor(Color4B::BLACK);
	lLoc->setAnchorPoint(Vec2(0.5, 0.5));
	lLoc->enableOutline(Color4B::BLACK, fontSize * 0.05);
	lLoc->setPosition(w * 0.5 - scalingHeight * 0.5,
			h * 0.5 + scalingHeight * 0.0);
	this->addChild(lLoc, 1);

	Color3B longColor(255, 32, 32);
	Color3B latColor(22, 196, 52);
	Color3B timeColor(22, 131, 196);
	Color3B dateColor(239, 32, 155);

	Sprite* platform = Sprite::create("platform.png");
	platform->setPosition(w - scalingHeight * 0.3,
			h * 0.5 + scalingHeight * 0.2);
	platform->setScale(scalingHeight * 0.4 / platform->getContentSize().height);
	this->addChild(platform, 1);

	{ // latitude
		Sprite* textBg = Sprite::create("text_bg.png");
		textBg->setScale(scalingHeight * 0.1 / textBg->getContentSize().height);
		textBg->setColor(latColor);
		textBg->setPosition(scalingHeight * 0.4, h * 0.5 - scalingHeight * 0.2);
		this->addChild(textBg, 1);
		textBg->setOpacity(138);

		Label* l = Label::createWithTTF("45.0", "fonts/trench100free.otf",
				fontSize);
		l->setTextColor(Color4B::BLACK);
		l->enableOutline(Color4B::BLACK, fontSize * 0.05);
		l->setPosition(textBg->getPosition());
		this->addChild(l, 2);
	}

	{ // Longitude
		Sprite* textBg = Sprite::create("text_bg.png");
		textBg->setScale(scalingHeight * 0.1 / textBg->getContentSize().height);
		textBg->setColor(longColor);
		textBg->setPosition(scalingHeight * 0.6, h * 0.5 - scalingHeight * 0.2);
		this->addChild(textBg, 1);
		textBg->setOpacity(138);

		Label* l = Label::createWithTTF("165.0", "fonts/trench100free.otf",
				fontSize);
		l->setTextColor(Color4B::BLACK);
		l->enableOutline(Color4B::BLACK, fontSize * 0.05);
		l->setPosition(textBg->getPosition());
		this->addChild(l, 2);
	}

	{ // Date
		Sprite* textBg = Sprite::create("text_bg.png");
		textBg->setScaleX(
				scalingHeight * 0.22 / textBg->getContentSize().height);
		textBg->setScaleY(
				scalingHeight * 0.1 / textBg->getContentSize().height);
		textBg->setColor(dateColor);
		textBg->setPosition(scalingHeight * 0.5,
				h * 0.5 - scalingHeight * 0.32);
		this->addChild(textBg, 1);
		textBg->setOpacity(138);

		Label* l = Label::createWithTTF("June 28", "fonts/trench100free.otf",
				fontSize);
		l->setTextColor(Color4B::BLACK);
		l->enableOutline(Color4B::BLACK, fontSize * 0.05);
		l->setPosition(textBg->getPosition());
		this->addChild(l, 2);
	}

	{
		Sprite* textBg = Sprite::create("text_bg.png");
		textBg->setScaleX(
				scalingHeight * 0.22 / textBg->getContentSize().height);
		textBg->setScaleY(
				scalingHeight * 0.1 / textBg->getContentSize().height);
		textBg->setColor(timeColor);
		textBg->setPosition(scalingHeight * 0.5,
				h * 0.5 - scalingHeight * 0.44);
		this->addChild(textBg, 1);
		textBg->setOpacity(138);

		Label* l = Label::createWithTTF("12:56 pm", "fonts/trench100free.otf",
				fontSize);
		l->setTextColor(Color4B::BLACK);
		l->enableOutline(Color4B::BLACK, fontSize * 0.05);
		l->setPosition(textBg->getPosition());
		this->addChild(l, 2);
	}

	Label* lAz = Label::createWithTTF("Sun Azimuth", "fonts/trench100free.otf",
			fontSize);
	lAz->setTextColor(Color4B::BLACK);
	lAz->setAnchorPoint(Vec2(1, 0.5));
	lAz->enableOutline(Color4B::BLACK, fontSize * 0.05);
	lAz->setPosition(w - scalingHeight * 0.5, h * 0.5 - scalingHeight * 0.2);
	this->addChild(lAz, 2);

	{ // sun az
		Sprite* textBg = Sprite::create("text_bg.png");
		textBg->setScale(scalingHeight * 0.08 / textBg->getContentSize().height);
		textBg->setColor(Color3B(255, 178, 55));
		textBg->setPosition(w - scalingHeight * 0.4,
				h * 0.5 - scalingHeight * 0.2);
		this->addChild(textBg, 1);
		textBg->setOpacity(166);

		Label* l = Label::createWithTTF("145.0", "fonts/trench100free.otf",
				fontSize);
		l->setTextColor(Color4B::BLACK);
		l->enableOutline(Color4B::BLACK, fontSize * 0.05);
		l->setPosition(textBg->getPosition());
		this->addChild(l, 2);
	}

	Label* lElv = Label::createWithTTF("Sun Elevation",
			"fonts/trench100free.otf", fontSize);
	lElv->setTextColor(Color4B::BLACK);
	lElv->setAnchorPoint(Vec2(1, 0.5));
	lElv->enableOutline(Color4B::BLACK, fontSize * 0.05);
	lElv->setPosition(w - scalingHeight * 0.5, h * 0.5 - scalingHeight * 0.3);
	this->addChild(lElv, 2);



	{ // sun elevation
		Sprite* textBg = Sprite::create("text_bg.png");
		textBg->setScale(scalingHeight * 0.08 / textBg->getContentSize().height);
		textBg->setColor(Color3B(255, 178, 55));
		textBg->setPosition(w - scalingHeight * 0.4, h * 0.5 - scalingHeight * 0.3);
		this->addChild(textBg, 1);
		textBg->setOpacity(166);

		Label* l = Label::createWithTTF("63.5", "fonts/trench100free.otf",
				fontSize);
		l->setTextColor(Color4B::BLACK);
		l->enableOutline(Color4B::BLACK, fontSize * 0.05);
		l->setPosition(textBg->getPosition());
		this->addChild(l, 2);
	}


	shadow = Sprite::create("shadow.png");
	shadow->setAnchorPoint(Vec2(0.0, 0.5));
	shadow->setScaleX(
			platform->getContentSize().width * 0.5
					/ shadow->getContentSize().width);
	shadow->setPosition(platform->getContentSize() * 0.5);
	shadow->runAction(RotateBy::create(30, 3600));
	platform->addChild(shadow, 1);

	sun = Sprite::create("sun.png");
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

	azSlider = SliderControl::create(Size(w * 0.8, thickness), 180, longColor);
	azSlider->setPosition(w * 0.5, sideGap);
	this->addChild(azSlider, 10);

	latSlider = SliderControl::create(Size(h * 0.9, thickness), 90, latColor);
	latSlider->setRotation(90);
	latSlider->setPosition(sideGap, h * 0.5);
	this->addChild(latSlider, 20);

	dateSlider = SliderControl::create(Size(w * 0.8, thickness), 1, dateColor);
	dateSlider->setPosition(w * 0.5, h - sideGap);
	this->addChild(dateSlider, 30);

	timeSlider = SliderControl::create(Size(h * 0.9, thickness), 1, timeColor);
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

void LayerMain::updateValues(float dt) {
	star->setPosition(azSlider->getValue(), latSlider->getValue());
}
