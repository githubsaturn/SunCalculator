#include "AppManager.h"
#include "AppConstants.h"
#include "LayerMain.h"
#include "ui/CocosGUI.h"
#include "spa.h"

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

	int i = 0;

	daysInMonth[i++] = 31;
	daysInMonth[i++] = 28;
	daysInMonth[i++] = 31;
	daysInMonth[i++] = 30;
	daysInMonth[i++] = 31;
	daysInMonth[i++] = 30;
	daysInMonth[i++] = 31;
	daysInMonth[i++] = 31;
	daysInMonth[i++] = 30;
	daysInMonth[i++] = 31;
	daysInMonth[i++] = 30;
	daysInMonth[i++] = 31;

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

	countries = Sprite::create("countries_.png");
	countries->setPosition(scalingHeight * 0.55, h * 0.75);
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
	lLoc->setAnchorPoint(Vec2(0.0, 0.5));
	lLoc->enableOutline(Color4B::BLACK, fontSize * 0.05);
	lLoc->setPosition(scalingHeight * 0.3, h * 0.5 + scalingHeight * 0.05);
	this->addChild(lLoc, 1);

	Color3B longColor(255, 32, 32);
	Color3B latColor(22, 196, 52);
	Color3B timeColor(22, 131, 196);
	Color3B dateColor(239, 32, 155);

	{ // latitude
		Node* textBg = ui::Scale9Sprite::create("text_bg.png");
		float textBgHeight = textBg->getContentSize().height;
		textBg->setContentSize(Size(textBgHeight * 2.5, textBgHeight));
		textBg->setScale(scalingHeight * 0.1 / textBg->getContentSize().height);
		textBg->setColor(latColor);
		textBg->setPosition(scalingHeight * 0.42,
				h * 0.5 - scalingHeight * 0.05);
		this->addChild(textBg, 1);
		textBg->setOpacity(138);

		Label* l = Label::createWithTTF("45.0", "fonts/trench100free.otf",
				fontSize);
		l->setTextColor(Color4B::BLACK);
		l->enableOutline(Color4B::BLACK, fontSize * 0.05);
		l->setPosition(textBg->getPosition());
		this->addChild(l, 2);
		labelLat = l;
	}

	{ // Longitude
		Node* textBg = ui::Scale9Sprite::create("text_bg.png");
		float textBgHeight = textBg->getContentSize().height;
		textBg->setContentSize(Size(textBgHeight * 2.5, textBgHeight));
		textBg->setScale(scalingHeight * 0.1 / textBg->getContentSize().height);
		textBg->setColor(longColor);
		textBg->setPosition(scalingHeight * 0.72,
				h * 0.5 - scalingHeight * 0.05);
		this->addChild(textBg, 1);
		textBg->setOpacity(138);

		Label* l = Label::createWithTTF("165.0", "fonts/trench100free.otf",
				fontSize);
		l->setTextColor(Color4B::BLACK);
		l->enableOutline(Color4B::BLACK, fontSize * 0.05);
		l->setPosition(textBg->getPosition());
		this->addChild(l, 2);
		labelLong = l;
	}

	{ // Date

		Node* textBg = ui::Scale9Sprite::create("text_bg.png");
		float textBgHeight = textBg->getContentSize().height;
		textBg->setContentSize(Size(textBgHeight * 5.5, textBgHeight));
		textBg->setScale(scalingHeight * 0.1 / textBg->getContentSize().height);
		textBg->setColor(dateColor);
		textBg->setPosition(scalingHeight * 0.57,
				h * 0.5 - scalingHeight * 0.17);
		this->addChild(textBg, 1);
		textBg->setOpacity(138);

		Label* l = Label::createWithTTF("June 28", "fonts/trench100free.otf",
				fontSize);
		l->setTextColor(Color4B::BLACK);
		l->enableOutline(Color4B::BLACK, fontSize * 0.05);
		l->setPosition(textBg->getPosition());
		this->addChild(l, 2);
		labelDate = l;
	}

	{ //time
		Node* textBg = ui::Scale9Sprite::create("text_bg.png");
		float textBgHeight = textBg->getContentSize().height;
		textBg->setContentSize(Size(textBgHeight * 5.5, textBgHeight));
		textBg->setScale(scalingHeight * 0.1 / textBg->getContentSize().height);
		textBg->setColor(timeColor);
		textBg->setPosition(scalingHeight * 0.57,
				h * 0.5 - scalingHeight * 0.29);
		this->addChild(textBg, 1);
		textBg->setOpacity(138);

		Label* l = Label::createWithTTF("12:56 pm", "fonts/trench100free.otf",
				fontSize);
		l->setTextColor(Color4B::BLACK);
		l->enableOutline(Color4B::BLACK, fontSize * 0.05);
		l->setPosition(textBg->getPosition());
		this->addChild(l, 2);
		labelTime = l;
	}

	{ //time zone
		Node* textBg = ui::Scale9Sprite::create("text_bg.png");
		float textBgHeight = textBg->getContentSize().height;
		textBg->setContentSize(Size(textBgHeight * 5.5, textBgHeight));
		textBg->setScale(scalingHeight * 0.1 / textBg->getContentSize().height);
		textBg->setColor(timeColor);
		textBg->setPosition(scalingHeight * 0.57,
				h * 0.5 - scalingHeight * 0.41);
		this->addChild(textBg, 1);
		textBg->setOpacity(138);

		Label* l = Label::createWithTTF("12:56 pm", "fonts/trench100free.otf",
				fontSize);
		l->setTextColor(Color4B::BLACK);
		l->enableOutline(Color4B::BLACK, fontSize * 0.05);
		l->setPosition(textBg->getPosition());
		this->addChild(l, 2);
		labelTimeZone = l;
	}

	Label* lAz = Label::createWithTTF("Sun Azimuth", "fonts/trench100free.otf",
			fontSize);
	lAz->setTextColor(Color4B::BLACK);
	lAz->setAnchorPoint(Vec2(1, 0.5));
	lAz->enableOutline(Color4B::BLACK, fontSize * 0.05);
	lAz->setPosition(w - scalingHeight * 0.5, h * 0.5 - scalingHeight * 0.41);
	this->addChild(lAz, 2);

	{ // sun az
		Node* textBg = ui::Scale9Sprite::create("text_bg.png");
		float textBgHeight = textBg->getContentSize().height;
		textBg->setContentSize(Size(textBgHeight * 3.0, textBgHeight));
		textBg->setScale(
				scalingHeight * 0.08 / textBg->getContentSize().height);
		textBg->setColor(Color3B(255, 178, 55));
		textBg->setPosition(w - scalingHeight * 0.36, h * 0.5 - scalingHeight * 0.41);

		this->addChild(textBg, 1);
		textBg->setOpacity(166);

		Label* l = Label::createWithTTF("145.0", "fonts/trench100free.otf",
				fontSize);
		l->setTextColor(Color4B::BLACK);
		l->enableOutline(Color4B::BLACK, fontSize * 0.05);
		l->setPosition(textBg->getPosition());
		this->addChild(l, 2);
		labelAz = l;
	}

	Label* lElv = Label::createWithTTF("Sun Elevation",
			"fonts/trench100free.otf", fontSize);
	lElv->setTextColor(Color4B::BLACK);
	lElv->setAnchorPoint(Vec2(1, 0.5));
	lElv->enableOutline(Color4B::BLACK, fontSize * 0.05);
	lElv->setPosition(w - scalingHeight * 0.5, h * 0.5 - scalingHeight * 0.29);
	this->addChild(lElv, 2);

	{ // sun elevation
		Node* textBg = ui::Scale9Sprite::create("text_bg.png");
		float textBgHeight = textBg->getContentSize().height;
		textBg->setContentSize(Size(textBgHeight * 3.0, textBgHeight));
		textBg->setScale(
				scalingHeight * 0.08 / textBg->getContentSize().height);
		textBg->setColor(Color3B(255, 178, 55));
		textBg->setPosition(w - scalingHeight * 0.36, h * 0.5 - scalingHeight * 0.29);
		this->addChild(textBg, 1);
		textBg->setOpacity(166);

		Label* l = Label::createWithTTF("63.5", "fonts/trench100free.otf",
				fontSize);
		l->setTextColor(Color4B::BLACK);
		l->enableOutline(Color4B::BLACK, fontSize * 0.05);
		l->setPosition(textBg->getPosition());
		this->addChild(l, 2);
		labelElv = l;
	}

	Sprite* platform = Sprite::create("platform.png");
	platform->setPosition(w - scalingHeight * 0.5,
			h * 0.5 + scalingHeight * 0.15);
	platform->setScale(scalingHeight * 0.6 / platform->getContentSize().height);
	this->addChild(platform, 1);

	shadow = Sprite::create("shadow.png");
	shadow->setAnchorPoint(Vec2(0.0, 0.5));
	shadowScale = platform->getContentSize().width * 0.5
			/ shadow->getContentSize().width;
	shadow->setScaleX(shadowScale);
	shadow->setPosition(platform->getContentSize() * 0.5);
	platform->addChild(shadow, 1);

	sun = Sprite::create("sun.png");
	sunDist = platform->getContentSize().height * 0.5;
	sun->setPosition(0, sunDist);
	platform->addChild(sun, 10);

	Sprite* object = Sprite::create("object.png");
	object->setAnchorPoint(Vec2(0.5, 0.3));
	object->setPosition(platform->getContentSize() * 0.5);
	platform->addChild(object, 10);

	float sideGap = w * 0.03f;
	float thickness = w * 0.007f;

	longSlider = SliderControl::create(Size(w * 0.8, thickness), 179.9,
			longColor);
	longSlider->setPosition(w * 0.5, h - sideGap);
	this->addChild(longSlider, 10);

	latSlider = SliderControl::create(Size(h * 0.9, thickness), 80, latColor);
	latSlider->setRotation(-90);
	latSlider->setPosition(sideGap, h * 0.5);
	this->addChild(latSlider, 20);

	dateSlider = SliderControl::create(Size(w * 0.8, thickness), 1, dateColor);
	dateSlider->setPosition(w * 0.5, sideGap);
	this->addChild(dateSlider, 30);

	timeSlider = SliderControl::create(Size(h * 0.9, thickness), 1, timeColor);
	timeSlider->setRotation(-90);
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

	float longitude = longSlider->getValue();
	float latitude = latSlider->getValue();

	int assumedTimeZone = longitude * 12 / 180;

	float maplongitude = longitude
			- (latitude / 40.0f) * (latitude / 40.0f) * longitude / 16.0f;

	float x = countries->getContentSize().width * (maplongitude * 1.04 + 160.0)
			/ 360.0f;
	float y = countries->getContentSize().height * (latitude * 1.28 + 75.0)
			/ 180.0f;

	star->setPosition(x, y);

	float dateValue = dateSlider->getValue();
	float timeValue = timeSlider->getValue();

	int day = (int) ((dateValue + 1.0) * 364 * 0.5 + 1);

	int month = 1;

	for (int idx = 0; idx < 12; ++idx) {
		if (day > daysInMonth[idx]) {
			day -= daysInMonth[idx];
			month++;
		} else {
			break;
		}
	}

	float hours = (timeValue + 1.0) * 12.0;

	int hour = (int) (hours);
	int minute = (int) ((hours - hour) * 60.0);

	std::string azStr = "--";
	std::string elvStr = "--";
	std::string dateStr("--");
	std::string timeStr = to_string(hour) + ":" + to_string(minute);

	spa_data spa; //declare the SPA structure

	{
		int result;
		float min, sec;

		//enter required input values into SPA structure

		spa.year = 2015;
		spa.month = month;
		spa.day = day;
		spa.hour = hour;
		spa.minute = minute;
		spa.second = 0;
		spa.timezone = assumedTimeZone;
		spa.delta_ut1 = 0;
		spa.delta_t = 67;
		spa.longitude = longitude;
		spa.latitude = latitude;
		spa.elevation = 500.14;
		spa.pressure = 1013;
		spa.temperature = 22;
		spa.slope = 0;
		spa.azm_rotation = -10;
		spa.atmos_refract = 0.5667;
		spa.function = SPA_ZA; //SPA_ALL

		//call the SPA calculate function and pass the SPA structure

		result = spa_calculate(&spa);

		if (result == 0) { //check for SPA errors
			//display the results inside the SPA structure

			char azBuf[50];
			sprintf(azBuf, "%.1f", (spa.azimuth));
			char elvBuf[50];
			sprintf(elvBuf, "%.1f", (90.0 - spa.zenith));

			azStr = std::string(azBuf);
			elvStr = std::string(elvBuf);

		} else {
			log("SPA Error Code: %d\n", result);
		}

	}

	char latBuf[50];
	sprintf(latBuf, "%.1f", (latitude));
	std::string latStr(latBuf);
	char longBuf[50];
	sprintf(longBuf, "%.1f", (longitude));
	std::string longStr(longBuf);

	if (month == 1)
		dateStr = "Jan";
	else if (month == 2)
		dateStr = "Feb";
	else if (month == 3)
		dateStr = "Mar";
	else if (month == 4)
		dateStr = "Apr";
	else if (month == 5)
		dateStr = "May";
	else if (month == 6)
		dateStr = "Jun";
	else if (month == 7)
		dateStr = "Jul";
	else if (month == 8)
		dateStr = "Aug";
	else if (month == 9)
		dateStr = "Sep";
	else if (month == 10)
		dateStr = "Oct";
	else if (month == 11)
		dateStr = "Nov";
	else if (month == 12)
		dateStr = "Dec";

	dateStr = dateStr + " " + to_string(day);

	labelLat->setString(latStr);
	labelLong->setString(longStr);

	labelDate->setString(dateStr);
	labelTime->setString(timeStr);

	labelAz->setString(azStr);
	labelElv->setString(elvStr);

	if (assumedTimeZone < 0)
		labelTimeZone->setString("Time Zone:  " + to_string(assumedTimeZone));
	else
		labelTimeZone->setString("Time Zone:  +" + to_string(assumedTimeZone));

	float s = sin(-spa.azimuth * 3.1415 / 180.0);
	float c = cos(-spa.azimuth * 3.1415 / 180.0);

	sun->setPosition(sunDist + sunDist * s, sunDist + sunDist * c);
	shadow->setRotation(-spa.azimuth + 90);
	if (spa.zenith < 90) {
		shadow->setScaleX(spa.zenith * shadowScale / 80);
		sun->setColor(Color3B::WHITE);
	} else {
		shadow->setScaleX(0.001);
		sun->setColor(Color3B::GRAY);
	}

}
