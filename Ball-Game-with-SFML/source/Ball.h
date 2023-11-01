#include "visiblegameobject.h"

#pragma once

class GameBall : public VisibleGameObject
{
    public:
        GameBall();
        virtual ~GameBall();
        void Update(float);  //���µ�������״̬

    private:
        float _velocity;  //�ٶ�
        float _angle;  //�ƶ��ķ���
        float _elapsedTimeSinceStart;  //��Ϸ��ʱ��

        float LinearVelocityX(float angle); //ˮƽ���ٶ�
        float LinearVelocityY(float angle);  //��ֱ���ٶ�
};
