//
//  Top.cpp
//  breakout
//
//  Created by dormouse666 on 2016/04/03.
//
//

#include "Top.h"

USING_NS_CC;

// コンストラクタ
Top::Top()
: _visibleSize(0,0)
, _origin(0,0)
, _backGround(nullptr)
, _ball(nullptr)
{
}

// デストラクタ
Top::~Top()
{
}

Scene* Top::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = Top::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// initは初期化
bool Top::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    return true;
}

// onEnterは生成
void Top::onEnter()
{
    Layer::onEnter();
    
    // 画面サイズ取得
    _visibleSize = Director::getInstance()->getVisibleSize();
    _origin = Director::getInstance()->getVisibleOrigin();
    
    // Homeに戻るボタン
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(Top::menuCloseCallback, this));
    closeItem->setPosition(Vec2(_origin.x + _visibleSize.width - closeItem->getContentSize().width/2 ,
                                _origin.y + closeItem->getContentSize().height/2));
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);
    
    // 背景配置
    _backGround = Node::create();
    if(_backGround)
    {
        CCLOG("ancherPos: %f, %f",_backGround->getAnchorPoint().x, _backGround->getAnchorPoint().y);
        CCLOG("pos: %f, %f", _backGround->getPosition().x, _backGround->getPosition().y);
        
        // 背景サイズとか
        _backGround->setContentSize({_visibleSize.width * 0.7f, _visibleSize.height * 0.6f});
        _backGround->setAnchorPoint(Point(0.5f, 0.5f));
        _backGround->setPosition(_origin.x + _visibleSize.width / 2, _origin.y + _visibleSize.height / 2);
        
        // 適当に色つけとく
        auto color = LayerGradient::create(Color4B(255, 255, 255, 255), Color4B(8, 8, 8, 255), Point(1, 1));
        color->setContentSize(_backGround->getContentSize());
        _backGround->addChild(color);
        
        CCLOG("ancherPos: %f, %f",_backGround->getAnchorPoint().x, _backGround->getAnchorPoint().y);
        CCLOG("pos: %f, %f", _backGround->getPosition().x, _backGround->getPosition().y);
        
        this->addChild(_backGround);
    }
    
    //entryBall
    this->entryBall();
    
    //update
    this->scheduleUpdate();
}

void Top::onExit()
{
    Layer::onExit();
}

// Homeに戻るボタン
void Top::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

//ボール発射ボタン
void Top::entryBall()
{
    auto entryBallBtn = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(Top::entryBallCallback, this));
    auto menu = Menu::create(entryBallBtn, NULL);
    menu->setAnchorPoint(Point(0.5f, 0.5f));
    menu->setPosition(_origin.x + _visibleSize.width / 2, _origin.y + entryBallBtn->getContentSize().height);
    this->addChild(menu);
    
    /*
    entryBallBtn->setPosition(Vec2(origin.x + (visibleSize.width / 2) - entryBallBtn->getContentSize().width/2 ,
                                   origin.y + entryBallBtn->getContentSize().height/2));
    auto menu = Menu::create(entryBallBtn, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu);
     */
    
    CCLOG("menu: %f, %f", menu->getPosition().x, menu->getPosition().y);
}

//ボール発射ボタン
void Top::entryBallCallback(Ref* pSender)
{
    if(_ball)
    {
        return;
    }
    
    _ball = cocos2d::Sprite::create("images/ball.png");
    _ball->setAnchorPoint(Point(0.5f, 0.5f));
    _ball->setPosition(_origin.x + _visibleSize.width / 2,
                       _origin.y + (_backGround->getPosition().y - _backGround->getContentSize().height / 2));
    this->addChild(_ball);
}

//update
void Top::update(float dt)
{
    if(!_ball)
    {
        return;
    }
    
    //上限
    auto topPos = _origin.y + (_backGround->getPosition().y + _backGround->getContentSize().height / 2);
    //下限
    auto underPos = _origin.y + (_backGround->getPosition().y - _backGround->getContentSize().height / 2);
    //左限
    //右限
    
    //動かす
    _ball->setPosition(_ball->getPosition().x,
                        _ball->getPosition().y + 1);
    
    //上にぶつかった時
    if(_ball->getPosition().y >= topPos)
    {
        //TODO: ボールの状態を変える class化

        //とりえず消しとく
        _ball->removeFromParent();
        _ball = nullptr;
    }
}