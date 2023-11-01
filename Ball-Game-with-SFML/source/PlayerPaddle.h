#include "VisibleGameObject.h"

#pragma once

class PlayerPaddle : public VisibleGameObject
{
    public:
        PlayerPaddle(void);
        ~PlayerPaddle(void);

        void Update(float elapsedTime);
        void Draw(sf::RenderWindow& rw);

        float GetVelocity() const;

    private:
        float _velocity;
        float _maxVelocity;
};
