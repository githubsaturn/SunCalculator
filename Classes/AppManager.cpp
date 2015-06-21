#include "AppManager.h"
#include "AppConstants.h"
#include "cocos2d.h"
//#include "Serializer.h"

USING_NS_CC;

AppManager *AppManager::pInstance = NULL;

AppManager* AppManager::getInstance() {

	if (!pInstance) {
		pInstance = new AppManager;

		struct tm y2000;
		y2000.tm_hour = 0;
		y2000.tm_min = 0;
		y2000.tm_sec = 0;
		y2000.tm_year = 100;
		y2000.tm_mon = 0;
		y2000.tm_mday = 1;
		pInstance->y2k = mktime(&y2000);

	}

	return pInstance;
}

std::string AppManager::generateString(int stringID) {

	std::string ret = "?";

	if (stringID == 1) { // Android License Key -- used for in-app-purchase setup

		std::string s3 = "OCXXXXXTls";
		std::string s1 = "OCXXXXXTls";
		std::string s5 = "OCXXXXXTls";
		std::string s2 = "OCXXXXXTls";
		std::string s4 = "OCXXXXXTls";

		ret = s1 + s2 + s3 + s4 + s5;

	} else if (stringID == 2) { // Parse Application ID -- to be unified

		ret = "dCmrxTlt0TwbSI6Yn6lmlP7lLzo1CvJmhrvx27pd";

	} else if (stringID == 3) { // Parse Client Id -- to be unified

		ret = "WQb7KkfDTdOWQO9lya6c8cjqkqmIdAne2AWKdxQO";

	} else if (stringID == 4) {

	} else if (stringID == 5) {

	} else if (stringID == 6) {

	} else if (stringID == 7) {

	} else if (stringID == 8) {

	} else if (stringID == 9) {

	} else if (stringID == 10) {

	} else if (stringID == 11) {

	} else if (stringID == 12) {

	} else if (stringID == 13) {

	} else if (stringID == 14) {

	} else if (stringID == 15) {

	}

	return ret;
}

void AppManager::runScene(int scenceID) {

	Scene *pScene = NULL;
	pScene = Scene::create();
	Node* mainNode = Node::create();
	pScene->addChild(mainNode, 1);

	activeScene = scenceID;

	if (scenceID == kSceneSplash) {

		auto sprite = Sprite::create("HelloWorld.png");
		mainNode->addChild(sprite, 10);

	} else if (scenceID == kSceneMain) {

//		auto layer_buttons = LayerMainMenuButtons::create();
//		auto layer_fb = LayerFacebook::create();
//		auto layer_connect_phone = LayerConnectToPhone::create();
//		auto layer_rank = LayerRanking::create();
//		auto layer_share = LayerShare::create();
//
//		auto layer_background = LiveBackground::create(0);
//		mainNode->addChild(layer_background, 10);
//		mainNode->addChild(layer_buttons, 20);
//		mainNode->addChild(layer_rank, 25);
//		mainNode->addChild(layer_fb, 40);
//		mainNode->addChild(layer_connect_phone, 50);
//		mainNode->addChild(layer_share, 60);

	}

	auto director = Director::getInstance();

	if ((isLandscapeMode) && (activeScene != kSceneSplash)) {
		mainNode->setRotation(90.0f);
		// which is actually height:
		mainNode->setPositionY(getVisibleSize().width);
	}

	if (director->getRunningScene() == NULL)
		director->runWithScene(pScene);
	else
		director->replaceScene(TransitionFade::create(1, pScene));

}

cocos2d::Size AppManager::getVisibleSize() {

	Size returnSize = Director::getInstance()->getVisibleSize();

//	return Size(320 * 1.15, 480 * 1.15); // normal iphone 4
//	return Size(320, 480); // the smallest thing, 0.5 x iphone 4
//	return Size(600, 800); // the most squary thing
//	return Size(640, 1136); // iphone 5s, very narrow
//  return Size(640, 855); // Close to iPad aspect ratio

	if ((isLandscapeMode) && (activeScene != kSceneSplash)) {
		returnSize = Size(returnSize.height, returnSize.width);
	} else {
		returnSize = Size(returnSize.width, returnSize.height);
	}

	return returnSize;

}

double AppManager::getTimeNow() {

	// returns seconds since 2000-01-Jan

	double seconds;
	time(&timer); /* get current time; same as: timer = time(NULL)  */
	seconds = difftime(timer, y2k);

	return seconds;
}

void AppManager::rotateScreen() {
	isLandscapeMode = !isLandscapeMode;
	runScene (kSceneMain);
}

void AppManager::saveData() {

	UserDefault* def = UserDefault::getInstance();

	//def->setBoolForKey(KEY_IS_SOUND_MUTE, SoundManager::getInstance()->getMuteSFX());

	//def->flush();

	log("_____ SAVING DATA DONE");

}

void AppManager::loadLocalData() {

	UserDefault* def = UserDefault::getInstance();
	//SoundManager::getInstance()->muteSoundFX(def->getBoolForKey(KEY_IS_SOUND_MUTE));
}
cocos2d::Point AppManager::getOrigin() {

	return Director::getInstance()->getVisibleOrigin();

}

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)

extern "C" {
	jstring Java_com_linaralabs_iap_util_JavaPurchaseManager_nativeGetString(
			JNIEnv* env, jobject thiz,
			jint stringIdx) {

		int intStringIdx = (int) stringIdx;

		std::string str = AppManager::getInstance()->generateString(intStringIdx);
		jstring jStr = env->NewStringUTF(str.c_str());
		return jStr;
	}
}

extern "C" {
	jstring Java_com_linaralabs_social_JavaSocialManager_nativeGetString(
			JNIEnv* env, jobject thiz,
			jint stringIdx) {

		int intStringIdx = (int) stringIdx;

		std::string str = AppManager::getInstance()->generateString(intStringIdx);
		jstring jStr = env->NewStringUTF(str.c_str());
		return jStr;
	}
}

#endif
