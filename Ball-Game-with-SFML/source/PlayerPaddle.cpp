#include "stdafx.h"
#include "PlayerPaddle.h"
#include "GameWindow.h"

//初始化最初速度和最大速度以及读取弹板图片并设置其初始位置
PlayerPaddle::PlayerPaddle() : _velocity(0),_maxVelocity(600.0f)
{
    Load("images/paddle.png");
    assert(IsLoaded());

    GetSprite().setOrigin(GetSprite().getLocalBounds().width / 2, GetSprite().getLocalBounds().height / 2);

}


PlayerPaddle::~PlayerPaddle(void)
{
}


void PlayerPaddle::Draw(sf::RenderWindow& rw)
{
    VisibleGameObject::Draw(rw);
}

//获取弹板当前速度
float PlayerPaddle::GetVelocity() const
{
    return _velocity;
}

//由系统消息中判断键盘按键，并让弹板做出相应移动，elapsedTime为更新的间隔，即fps
void PlayerPaddle::Update(float elapsedTime)
{

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        _velocity -= 3.0f;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        _velocity += 3.0f;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        _velocity = 0.0f;
    }

    //如果弹板速度大于最大速度，就让其等于最大速度，最小速度也同理可得
    if (_velocity > _maxVelocity)
        _velocity = _maxVelocity;

    if (_velocity < -_maxVelocity)
        _velocity = -_maxVelocity;

    //获取弹板当前位置，判断其是否到达游戏窗体边界，到达则令其速度反向
    sf::Vector2f pos = this->GetPosition();

    if (pos.x  < GetSprite().getLocalBounds().width / 2
        || pos.x >(Game::SCREEN_WIDTH - GetSprite().getLocalBounds().width / 2))
    {
        _velocity = -_velocity;
    }
    //_velocity * elapsedTime为弹板移动距离
    GetSprite().move(_velocity * elapsedTime, 0);
}