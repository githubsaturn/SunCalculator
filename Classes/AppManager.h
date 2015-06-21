#ifndef  _APP_MANAGER_
#define  _APP_MANAGER_

#include "cocos2d.h"

template<typename T>
std::string to_string(T value) {
	std::ostringstream os;
	os << value;
	return os.str();
}

class AppManager {
public:

	static AppManager* getInstance();
	std::string generateString(int stringID);

	cocos2d::Size getVisibleSize();
	cocos2d::Point getOrigin();

	//	 ------------------------------------------------------------
	//  -------------    Helpers    ---------------------------------
	//	 ------------------------------------------------------------
	double getTimeNow();

	//	 ------------------------------------------------------------
	//  ------------- Game Managing ---------------------------------
	//	 ------------------------------------------------------------
	void runScene(int scenceID);

	void saveData();
	void loadLocalData();

	void rotateScreen();

	//	 ------------------------------------------------------------
	//	 ------------------------------------------------------------
	//	 --------- GETTER SETTER ------------------------------------
	//	 ------------------------------------------------------------
	//	 ------------------------------------------------------------

	int getActiveScence() {
		return activeScene;
	}

	bool getIsLandscapeMode() {
		return isLandscapeMode;
	}

private:

	static AppManager* pInstance;
	time_t timer; // temporary variable used to get time
	time_t y2k; // temporary variable used to get time

	int activeScene = -1;

	//bool isGameSocial;
	bool isLandscapeMode = false;

};

#endif
