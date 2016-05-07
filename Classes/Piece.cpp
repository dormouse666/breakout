//
//  Piece.cpp
//  breakout
//
//  Created by dormouse666 on 2016/05/07.
//
//

#include "Piece.h"

USING_NS_CC;

//コンストラクタ
Piece::Piece()
: _piece(nullptr)
{
}

// デストラクタ
Piece::~Piece()
{
}

// initは初期化
bool Piece::init()
{
    if ( !Node::init() )
    {
        return false;
    }
    
    return true;
}

// onEnterは生成
void Piece::onEnter()
{
    Node::onEnter();
    
    setUpPiece(RED); //TODO:色をランダムに
}

void Piece::onExit()
{
    Node::onExit();
}

void Piece::setUpPiece(ColorType type)
{
    //前のスプライト消す
    if(_piece)
    {
        _piece->removeFromParent();
        _piece = nullptr;
    }
    
    //テーブル化する
    static std::map<ColorType, const char*> imgPathTbl = {
        {BLUE, "images/block1.png"},
        {GREEN, "images/block2.png"},
        {RED, "images/block3.png"},
    };
    
    //要素チェック
    if(imgPathTbl.find(type) == imgPathTbl.end())
    {
        return;
    }

    //スプライト作る
    _piece = Sprite::create(imgPathTbl[type]);
    if(_piece)
    {
        this->addChild(_piece);
    }
}

