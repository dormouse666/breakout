//
//  Top.h
//  breakout
//
//  Created by dormouse666 on 2016/04/03.
//
//

#ifndef __breakout__Top__
#define __breakout__Top__

#include "cocos2d.h"

class Top : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    
    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(Top);
    
    // ここから
    Top();
    virtual ~Top();
    
    void onEnter() override;
    void onExit() override;
    
    void entryBall();
    void entryBallCallback(cocos2d::Ref* pSender);
    
    void update(float dt);
    
private:
    cocos2d::Size _visibleSize;
    cocos2d::Vec2 _origin;
    cocos2d::Node* _backGround;
    cocos2d::Sprite* _ball;
};

#endif /* defined(__breakout__Top__) */
