#include "GameOverScene.h"
#include "GameScene.h"
#include "MainMenuScene.h"
#include "Definitions.h"


USING_NS_CC;

unsigned int score = 0;

Scene* GameOverScene::createScene(unsigned int tempScore)
{
	score = tempScore;

    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = GameOverScene::create();

	// add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool GameOverScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto backgroundSprite = Sprite::create("Background.png");
	backgroundSprite->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

	this->addChild(backgroundSprite);

    
	auto retryItem = MenuItemImage::create("Retry Button.png", "Retry Button Clicked.png", CC_CALLBACK_1(GameOverScene::GoToGameScene, this));
	retryItem->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 4 * 3));
	
	auto mainMenuItem = MenuItemImage::create("Menu Button.png", "Menu Button Clicked.png", CC_CALLBACK_1(GameOverScene::GoToMainMenuScene, this));
	mainMenuItem->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 4));
    
	auto menu = Menu::create(retryItem, mainMenuItem, NULL);
	menu->setPosition(Point::ZERO);

	this->addChild(menu);
	// PERMITE GUARDAR LA INFORMACIÓN 
	UserDefault *def = UserDefault::getInstance();

	auto highScore = def->getIntegerForKey("HIGHSCORE FLAPPY", 0);
	auto myname = def->getStringForKey("my_name", "......");
	
	if (score > highScore)
	{
		highScore = score;
		myname = "Juanma";
		// seteamos la llave HIGHSCORE FLAPPY CON EL NUEVO VALOR 
		//def->setIntegerForKey("HIGHSCORE FLAPPY", highScore);
		
		def->setStringForKey("my_name", myname);
	}
	else if (score > highScore) {
		myname = "Yokohomo";
		// seteamos la llave HIGHSCORE FLAPPY CON EL NUEVO VALOR 
		//def->setIntegerForKey("HIGHSCORE FLAPPY", highScore);

		def->setStringForKey("my_name", myname);
	}
	else {
		myname = "MIroslav";
		// seteamos la llave HIGHSCORE FLAPPY CON EL NUEVO VALOR 
		//def->setIntegerForKey("HIGHSCORE FLAPPY", highScore);

		def->setStringForKey("my_name", myname);
	}
	
	// flush : se encarga de guardar la info en un archivo .xml
	def->flush();

	__String *tempName = __String::createWithFormat("%c", myname);
	

	auto currentName = LabelTTF::create(tempName->getCString(), "fonts/Marker Felt.ttf", visibleSize.height * SCORE_FONT_SIZE);
	currentName->setPosition(Point(visibleSize.width * 0.25 + origin.x, visibleSize.height / 2 + origin.y));

	this->addChild(currentName);
	//__String *tempScore = __String::createWithFormat("%i", score);
	
	__String *tempHighName = __String::createWithFormat("%s", myname);

	auto highNameLabel = LabelTTF::create(tempHighName->getCString(), "fonts/Marker Felt.ttf", visibleSize.height * SCORE_FONT_SIZE);

	highNameLabel->setColor(Color3B::YELLOW);
	highNameLabel->setPosition(Point(visibleSize.width * 0.75 + origin.x, visibleSize.height / 2 + origin.y));

	this->addChild(highNameLabel);
	
	return true;
}

void GameOverScene::GoToMainMenuScene(cocos2d::Ref *sender) {
	auto scene = MainMenuScene::createScene();
	Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
}
void  GameOverScene::GoToGameScene(cocos2d::Ref *sender) {
	auto scene = GameScene::createScene();
	Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
}
