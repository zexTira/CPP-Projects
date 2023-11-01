#include "stdafx.h"
#include "PlayerPaddle.h"
#include "GameWindow.h"

//��ʼ������ٶȺ�����ٶ��Լ���ȡ����ͼƬ���������ʼλ��
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

//��ȡ���嵱ǰ�ٶ�
float PlayerPaddle::GetVelocity() const
{
    return _velocity;
}

//��ϵͳ��Ϣ���жϼ��̰��������õ���������Ӧ�ƶ���elapsedTimeΪ���µļ������fps
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

    //��������ٶȴ�������ٶȣ��������������ٶȣ���С�ٶ�Ҳͬ��ɵ�
    if (_velocity > _maxVelocity)
        _velocity = _maxVelocity;

    if (_velocity < -_maxVelocity)
        _velocity = -_maxVelocity;

    //��ȡ���嵱ǰλ�ã��ж����Ƿ񵽴���Ϸ����߽磬�����������ٶȷ���
    sf::Vector2f pos = this->GetPosition();

    if (pos.x  < GetSprite().getLocalBounds().width / 2
        || pos.x >(Game::SCREEN_WIDTH - GetSprite().getLocalBounds().width / 2))
    {
        _velocity = -_velocity;
    }
    //_velocity * elapsedTimeΪ�����ƶ�����
    GetSprite().move(_velocity * elapsedTime, 0);
}