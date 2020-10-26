#include "Laser.hpp"
#include "Game.hpp"
#include "MovementComponent.hpp"
#include "SpriteComponent.hpp"
#include "CircleComponent.hpp"
#include "Asteroid.hpp"

Laser::Laser(Game* game)
    : Actor(game), mDeathTimer(1.f)
{
    MovementComponent* movement = new MovementComponent(this, 2);
    movement->SetForwardSpeed(500.f);
    
    SpriteComponent* sprite = new SpriteComponent(this, 3);
    sprite->SetTexture(game->GetTexture("/Assets/Laser.png"));
    
    mCircle = new CircleComponent(this, 4);
    mCircle->SetRadius(10.f);
}

void Laser::UpdateActor(float deltaTime)
{
    mDeathTimer -= deltaTime;
    if (mDeathTimer <= 0.f)
        SetState(EDisable);
    else
    {
        for (auto asteroid : GetGame()->GetAsteroids())
        {
            if (Intersect(*mCircle, *(asteroid->GetCircle())))
            {
                SetState(EDisable);
                asteroid->SetState(EDisable);
                break;
            }
        }
    }
}
