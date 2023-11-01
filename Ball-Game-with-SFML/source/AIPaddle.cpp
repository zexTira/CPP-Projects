#include "StdAfx.h"
#include "AIPaddle.h"
#include "GameWindow.h"
#include "Ball.h"

AIPaddle::AIPaddle() :
    _velocity(0),
    _maxVelocity(600.0f)
{
    Load("images/paddle.png");
    assert(IsLoaded());

    GetSprite().setOrigin(GetSprite().getLocalBounds().width / 2, GetSprite().getLocalBounds().height / 2);
}


AIPaddle::~AIPaddle()
{
}

void AIPaddle::Draw(sf::RenderWindow& rw)
{
    VisibleGameObject::Draw(rw);
}

float AIPaddle::GetVelocity() const
{
    return _velocity;
}

void AIPaddle::Update(float elapsedTime)
{
    const GameBall* gameBall = static_cast<GameBall*>
        (Game::GetGameObjectManager().Get("Ball"));
    sf::Vector2f ballPosition = gameBall->GetPosition();

    if (GetPosition().x - 20 < ballPosition.x)
        _velocity += 15.0f;
    else if (GetPosition().x + 20 > ballPosition.x)
        _velocity -= 10.0f;
    else
        _velocity = 0.0f;


    if (_velocity > _maxVelocity)
        _velocity = _maxVelocity;

    if (_velocity < -_maxVelocity)
        _velocity = -_maxVelocity;


    sf::Vector2f pos = this->GetPosition();

    if (pos.x <= GetSprite().getLocalBounds().width / 2
        || pos.x >= (Game::SCREEN_WIDTH - GetSprite().getLocalBounds().width / 2))
    {
        _velocity = -_velocity;
    }

    GetSprite().move(_velocity * elapsedTime, 0);
}