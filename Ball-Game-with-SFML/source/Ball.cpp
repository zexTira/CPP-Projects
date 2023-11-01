#include "stdafx.h"
#include "Ball.h"
#include "GameWindow.h"
#include "AIPaddle.h"

GameBall::GameBall() :
    _velocity(230.0f),
    _elapsedTimeSinceStart(0.0f)
{
    //assert�������ã���������ı��ʽ���뷵��true��������false������ϵͳ����
    Load("images/ball.png");
    assert(IsLoaded());

    GetSprite().setOrigin(15, 15);

    //���õ�����ƶ�����Ϊ1��360֮������ֵ
    _angle = std::rand() % 360 + 1;
    //_angle = (float)(sf::Randomizer::Random(0,360);
}


GameBall::~GameBall()
{
}


void GameBall::Update(float elapsedTime)
{
    _elapsedTimeSinceStart += elapsedTime;

    // ���õ����ڿ�ʼ��Ϸ3���ſ�ʼ����
    if (_elapsedTimeSinceStart < 3.0f)
        return;

    //����ÿ֡���ƶ�����
    float moveAmount = _velocity * elapsedTime;

    //ˮƽλ��
    float moveByX = LinearVelocityX(_angle) * moveAmount;
    //��ֱλ��
    float moveByY = LinearVelocityY(_angle) * moveAmount;


    //��ȡ��ҵ���
    PlayerPaddle* player1 = dynamic_cast<PlayerPaddle*>(Game::GetGameObjectManager().Get("Paddle1"));
    if (player1 != NULL)
    {
        //�洢��ҵ���ľ�������
        sf::Rect<float> p1BB = player1->GetBoundingRect();

        //�����ҵ���ľ��������뵯��ľ��������Ƿ����ص�
        //�����ʾ��������ײ��Ȼ������ط�����ϸ��
        if (p1BB.intersects(GetBoundingRect()))
        {
            _angle = 360.0f - (_angle - 180.0f);
            if (_angle > 360.0f)
                _angle -= 360.0f;

            moveByY = -moveByY;

            // ȷ�����򲻻��ܵ�����ľ���������
            if (GetBoundingRect().width > player1->GetBoundingRect().top)
            {
                SetPosition(GetPosition().x, player1->GetBoundingRect().top - GetWidth() / 2 - 1);
            }


            float playerVelocity1 = player1->GetVelocity();

            //�����������ƶ�ʱ
            if (playerVelocity1 < 0)
            {
                //ʹ����Ƕȼ���
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
            //ÿ����ײ���嶼ʹ�����ٶ�����
            _velocity += 5.0f;
        }

    }



    //����AI������
    AIPaddle* player2 = dynamic_cast<AIPaddle*>(Game::GetGameObjectManager().Get("Paddle2"));
    if (player2 != NULL)
    {
        //�洢AI����ľ�������
        sf::Rect<float> p2BB = player2->GetBoundingRect();

        //���AI����ľ��������뵯��ľ��������Ƿ����ص�
        //�����ʾ��������ײ��Ȼ������ط�����ϸ��
        if (p2BB.intersects(GetBoundingRect()))
        {
            _angle = 360.0f - (_angle - 180.0f);
            if (_angle > 360.0f)
                _angle -= 360.0f;

            moveByY = -moveByY;

            // ȷ�����򲻻��ܵ�����ľ���������
            if (GetBoundingRect().width > player2->GetBoundingRect().width)
            {
                SetPosition(GetPosition().x, player2->GetBoundingRect().width - GetWidth() / 2 - 1);
            }


            float playerVelocity2 = player2->GetVelocity();

            //�����������ƶ�ʱ
            if (playerVelocity2 < 0)
            {
                //ʹ����Ƕȼ���
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
            //ÿ����ײ���嶼ʹ�����ٶ�����
            _velocity += 5.0f;
        }
    }


    //��������ײ����Ļ����ʱ�Ĵ���
    if (GetPosition().x + moveByX <= 0 + GetWidth() / 2
        || GetPosition().x + GetHeight() / 2 + moveByX >= Game::SCREEN_WIDTH)
    {
        //���������Լ�����ˮƽλ��ʹ�䷴��
        _angle = 360.0f - _angle;
        if (_angle > 260.0f && _angle < 280.0f)
            _angle += 20.0f;
        if (_angle > 80.0f && _angle < 100.0f)
            _angle += 20.0f;
        moveByX = -moveByX;
    }


    //��������ײ����Ļ�Ϸ������䷴��
    if (GetPosition().y - GetHeight() / 2 <= 0)
    {
        //         _angle =  180 - _angle;
        //         moveByY = -moveByY;        
        GetSprite().setPosition(Game::SCREEN_WIDTH / 2, Game::SCREEN_HEIGHT / 2);
        _angle = std::rand() % 360 + 1;
        _velocity = 220.0f;
        _elapsedTimeSinceStart = 0.0f;
    }


    //�������䵽�ȵ���͵ĵط������õ���
    if (GetPosition().y + GetHeight() / 2 + moveByY >= Game::SCREEN_HEIGHT)
    {
        GetSprite().setPosition(Game::SCREEN_WIDTH / 2, Game::SCREEN_HEIGHT / 2);
        _angle = std::rand() % 360 + 1;
        _velocity = 220.0f;
        _elapsedTimeSinceStart = 0.0f;
    }


    //������ƶ�����
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