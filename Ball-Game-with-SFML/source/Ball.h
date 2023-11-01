#include "visiblegameobject.h"

#pragma once

class GameBall : public VisibleGameObject
{
    public:
        GameBall();
        virtual ~GameBall();
        void Update(float);  //更新弹球属性状态

    private:
        float _velocity;  //速度
        float _angle;  //移动的方向
        float _elapsedTimeSinceStart;  //游戏总时间

        float LinearVelocityX(float angle); //水平线速度
        float LinearVelocityY(float angle);  //垂直线速度
};
