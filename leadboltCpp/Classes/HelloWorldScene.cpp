#include "HelloWorldScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

#include "PluginLeadBolt/PluginLeadBolt.h"

USING_NS_CC;

using namespace cocostudio::timeline;

class LBListener : public sdkbox::LeadBoltListener {
public:
    
    virtual void onModuleLoaded(const std::string& placement) {
        CCLOG("onModuleLoaded placement:%s", placement.c_str());
    }
    virtual void onModuleClosed(const std::string& placement) {
        CCLOG("onModuleClosed placement:%s", placement.c_str());
    }
    virtual void onModuleClicked(const std::string& placement) {
        CCLOG("onModuleClicked placement:%s", placement.c_str());
    }
    virtual void onModuleCached(const std::string& placement) {
        CCLOG("onModuleCached placement:%s", placement.c_str());
    }
    virtual void onModuleFailed(const std::string& placement, const std::string& error, bool iscached) {
        CCLOG("onModuleFailed placement:%s, error:%s, cached:%d", placement.c_str(), error.c_str(), iscached);
    }
    virtual void onMediaFinished(bool viewCompleted) {
        CCLOG("onMediaFinished viewCompleted:%d", viewCompleted);
    }
};

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
//    auto rootNode = CSLoader::createNode("MainScene.csb");
//
//    addChild(rootNode);
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    auto label = Label::createWithTTF("LeadBolt Sample", "fonts/Marker Felt.ttf", 24);
    
    // position the label on the center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));
    
    // add the label as a child to this layer
    this->addChild(label, 1);
    
    Menu* list = Menu::create(
                              MenuItemFont::create("Cache", CC_CALLBACK_1(HelloWorld::onButtonCache, this)),
                              MenuItemFont::create("Show", CC_CALLBACK_1(HelloWorld::onButtonShow, this)),
                              NULL);
    list->alignItemsVerticallyWithPadding(5);
    list->setPosition(origin.x + visibleSize.width/2, origin.y + visibleSize.height/2);
    addChild(list);
    
    sdkbox::PluginLeadBolt::setListener(new LBListener());
    sdkbox::PluginLeadBolt::init();

    return true;
}


void HelloWorld::onButtonCache(Ref *sender) {
    std::string name = "ad1";
    sdkbox::PluginLeadBolt::loadModuleToCache(name);
}

void HelloWorld::onButtonShow(Ref *sender) {
    std::string name = "ad1";
    if (sdkbox::PluginLeadBolt::isAdReady(name)) {
        CCLOG("leadbolt ad is ready, load");
        sdkbox::PluginLeadBolt::loadModule(name);
    } else {
        CCLOG("leadbolt ad is not ready");
    }
}
