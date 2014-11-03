#include "HelloWorldScene.h"

USING_NS_CC;

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
    
    // シングルタップ用リスナーを用意する
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(_swallowsTouches);
    
    // 各イベントの割当
    listener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(HelloWorld::onTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(HelloWorld::onTouchEnded, this);
    listener->onTouchCancelled = CC_CALLBACK_2(HelloWorld::onTouchCancelled, this);
    
    // イベントディスパッチャにシングルタップ用リスナーを追加する
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));

	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    /*auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);*/

    // ボタンを管理するメニューを作成し、closeItemを登録する
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Point::ZERO);
    this->addChild(menu, 1);
    
    // 「Hello World」を表示するラベルを画面に追加する
    auto label = LabelTTF::create("Hello World", "Arial", 48);
    
    // labelを画面の上部に配置する
    label->setPosition(Point(visibleSize.width/2,
                             visibleSize.height - label->getContentSize().height * 0.75));

    // labelを時計回りに45度回転する
    label->setRotation(45);
    
    // add the label as a child to this layer
    this->addChild(label, 1);

    // add "HelloWorld" splash screen"
    auto sprite = Sprite::create("HelloWorld.png");

    // spriteをPoint(0,0)に配置する
    sprite->setPosition(Point(visibleSize.width/2, visibleSize.height/2));

    // spriteのアンカーポイントを画像の左下隅とする
    sprite->setAnchorPoint(Point(1, 1));
    
    // spriteを1/2に縮小する
    sprite->setScale(1.0);
    
    // add the sprite as a child to this layer
    this->addChild(sprite, 0);
    
    // 移動アクションを用意する
    auto move = MoveBy::create(2, Point(100, 100));
    
    // 回転アクションを用意する
    auto rotate = RotateBy::create(5, 90);
    
    // アクションを連結する
    auto spawn = Spawn::create(move, rotate, nullptr);
    
    // spriteにアクションを与える
    sprite->runAction(spawn);
    
    return true;
}

bool HelloWorld::onTouchBegan(Touch *touch, Event *unused_event)
{
    // タップ開始時の処理
    CCLOG("onTouchBegan");
    
    return true;
}

void HelloWorld::onTouchMoved(Touch *touch, Event *unused_event)
{
    // スワイプ中の処理
    CCLOG("onTouchMoved");
}

void HelloWorld::onTouchEnded(Touch *touch, Event *unused_event)
{
    // タップ終了の処理
    CCLOG("onTouchEnded");
}

void HelloWorld::onTouchCancelled(Touch *touch, Event *unused_event)
{
    // タップイベントのキャンセル時処理
    CCLOG("onTouchCanselled");
}
void HelloWorld::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    //Director::getInstance()->end();
    
    // 新しく画面を用意する
    auto scene = HelloWorld::createScene();
    
    // フェードアニメーションの設定
    auto tran = TransitionFade::create(2, scene);
    
    // 新しい画面に遷移する
    Director::getInstance()->replaceScene(tran);

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
