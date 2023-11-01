#include "stdafx.h"
#include "Ball.h"
#include "GameWindow.h"
#include "AIPaddle.h"

GameBall::GameBall() :
    _velocity(230.0f),
    _elapsedTimeSinceStart(0.0f)
{
    //assert方法作用：括号里面的表达式必须返回true，若返回false则会出现系统错误
    Load("images/ball.png");
    assert(IsLoaded());

    GetSprite().setOrigin(15, 15);

    //设置弹球的移动方向为1到360之间的随机值
    _angle = std::rand() % 360 + 1;
    //_angle = (float)(sf::Randomizer::Random(0,360);
}


GameBall::~GameBall()
{
}


void GameBall::Update(float elapsedTime)
{
    _elapsedTimeSinceStart += elapsedTime;

    // 设置弹球在开始游戏3秒后才开始更新
    if (_elapsedTimeSinceStart < 3.0f)
        return;

    //弹球每帧的移动距离
    float moveAmount = _velocity * elapsedTime;

    //水平位移
    float moveByX = LinearVelocityX(_angle) * moveAmount;
    //垂直位移
    float moveByY = LinearVelocityY(_angle) * moveAmount;


    //获取玩家弹板
    PlayerPaddle* player1 = dynamic_cast<PlayerPaddle*>(Game::GetGameObjectManager().Get("Paddle1"));
    if (player1 != NULL)
    {
        //存储玩家弹板的矩形区域
        sf::Rect<float> p1BB = player1->GetBoundingRect();

        //检测玩家弹板的矩形区域与弹球的矩形区域是否有重叠
        //有则表示发生了碰撞，然后处理相关反弹的细节
        if (p1BB.intersects(GetBoundingRect()))
        {
            _angle = 360.0f - (_angle - 180.0f);
            if (_angle > 360.0f)
                _angle -= 360.0f;

            moveByY = -moveByY;

            // 确保弹球不会跑到弹板的矩形区域内
            if (GetBoundingRect().width > player1->GetBoundingRect().top)
            {
                SetPosition(GetPosition().x, player1->GetBoundingRect().top - GetWidth() / 2 - 1);
            }


            float playerVelocity1 = player1->GetVelocity();

            //当弹板向左移动时
            if (playerVelocity1 < 0)
            {
                //使弹球角度减少
                _angle -= 20.0f;
                if (_angle < 0)
                    _angle = 360.0f - _angle;
            }
            else if (playerVelocity1 > 0)
            {
                _angle += 20.0f;
                if (_angle > 360.0f)
                    _angle = _angle - 360.0f;
            }
            //每次碰撞弹板都使弹球速度增加
            _velocity += 5.0f;
        }

    }



    //敌人AI的设置
    AIPaddle* player2 = dynamic_cast<AIPaddle*>(Game::GetGameObjectManager().Get("Paddle2"));
    if (player2 != NULL)
    {
        //存储AI弹板的矩形区域
        sf::Rect<float> p2BB = player2->GetBoundingRect();

        //检测AI弹板的矩形区域与弹球的矩形区域是否有重叠
        //有则表示发生了碰撞，然后处理相关反弹的细节
        if (p2BB.intersects(GetBoundingRect()))
        {
            _angle = 360.0f - (_angle - 180.0f);
            if (_angle > 360.0f)
                _angle -= 360.0f;

            moveByY = -moveByY;

            // 确保弹球不会跑到弹板的矩形区域内
            if (GetBoundingRect().width > player2->GetBoundingRect().width)
            {
                SetPosition(GetPosition().x, player2->GetBoundingRect().width - GetWidth() / 2 - 1);
            }


            float playerVelocity2 = player2->GetVelocity();

            //当弹板向左移动时
            if (playerVelocity2 < 0)
            {
                //使弹球角度减少
                _angle -= 20.0f;
                if (_angle < 0)
                    _angle = 360.0f - _angle;
            }
            else if (playerVelocity2 > 0)
            {
                _angle += 20.0f;
                if (_angle > 360.0f)
                    _angle = _angle - 360.0f;
            }
            //每次碰撞弹板都使弹球速度增加
            _velocity += 5.0f;
        }
    }


    //当弹球碰撞到屏幕两边时的处理
    if (GetPosition().x + moveByX <= 0 + GetWidth() / 2
        || GetPosition().x + GetHeight() / 2 + moveByX >= Game::SCREEN_WIDTH)
    {
        //调整方向以及更改水平位移使其反弹
        _angle = 360.0f - _angle;
        if (_angle > 260.0f && _angle < 280.0f)
            _angle += 20.0f;
        if (_angle > 80.0f && _angle < 100.0f)
            _angle += 20.0f;
        moveByX = -moveByX;
    }


    //当弹球碰撞到屏幕上方则令其反弹
    if (GetPosition().y - GetHeight() / 2 <= 0)
    {
        //         _angle =  180 - _angle;
        //         moveByY = -moveByY;        
        GetSprite().setPosition(Game::SCREEN_WIDTH / 2, Game::SCREEN_HEIGHT / 2);
        _angle = std::rand() % 360 + 1;
        _velocity = 220.0f;
        _elapsedTimeSinceStart = 0.0f;
    }


    //当弹球落到比弹板低的地方则重置弹球
    if (GetPosition().y + GetHeight() / 2 + moveByY >= Game::SCREEN_HEIGHT)
    {
        GetSprite().setPosition(Game::SCREEN_WIDTH / 2, Game::SCREEN_HEIGHT / 2);
        _angle = std::rand() % 360 + 1;
        _velocity = 220.0f;
        _elapsedTimeSinceStart = 0.0f;
    }


    //弹球的移动函数
    GetSprite().move(moveByX, moveByY);

}

float GameBall::LinearVelocityX(float angle)
{
    angle -= 90;
    if (angle < 0)
        angle = 360 + angle;
    return (float)std::cos(angle * (3.1415926 / 180.0f));
}

float GameBall::LinearVelocityY(float angle)
{
    angle -= 90;
    if (angle < 0)
        angle = 360 + angle;
    return (float)std::sin(angle * (3.1415926 / 180.0f));
}