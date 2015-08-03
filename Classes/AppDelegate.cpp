#include "AppDelegate.h"
#include "GameLayer/InVerifyLayer.h"
#include "trace_worker.h"
#include "net_server.h"
#include "SimpleIni.h"

USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

bool AppDelegate::applicationDidFinishLaunching() {
	CNetServer::instance()->startServer();

	CSimpleIniA ini;  
	ini.SetUnicode();  
	ini.LoadFile("Config.ini");  
	const char * netCliIp = ini.GetValue("NetConfig", "NetCliIp", "default");  
	int netCliPort = (int)ini.GetLongValue("NetConfig", "NetCliPort");

	trace_start(netCliIp, netCliPort, "Debug11.cpp");
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
        glview = GLViewImpl::createWithRect("My Game",Rect(0,0,320,568));
        director->setOpenGLView(glview);
    }

    // turn on display FPS
    director->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);

    std::vector<std::string> searchPath;
    searchPath.push_back("FlyShoot");
	searchPath.push_back("LogView");
    CCFileUtils::getInstance()->setSearchPaths(searchPath);

    // create a scene. it's an autorelease object
    auto scene = InVerifyLayer::createScene();

    // run
    director->runWithScene(scene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
