#include <string>

#include "Asteroid.hpp"
#include "Game.hpp"
#include "MovementComponent.hpp"
#include "SpriteComponent.hpp"
#include "CircleComponent.hpp"
#include "CML.hpp"

Asteroid::Asteroid(Game* game)
    : Actor(game), mCircle(nullptr)
{
    CML::Vector2D randomPosition = CML::Random::GetRandomVector2D(CML::Vector2D(0.f, 0.f), CML::Vector2D(512.f, 512.f));
    SetPosition(randomPosition);
    
    SetRotation(CML::Random::GetRandomFloat(0.f, CML::Pi * 2.f));
    
    MovementComponent* movement = new MovementComponent(this, 2);
    movement->SetForwardSpeed(100.f);
    
    SpriteComponent* sprite = new SpriteComponent(this, 3);
    sprite->SetTexture(game->GetTexture("/Assets/Asteroid.png"));
    
    mCircle = new CircleComponent(this, 4);
    mCircle->SetRadius(40.f);
    
    game->AddAsteroid(this);
}

Asteroid::~Asteroid()
{
    GetGame()->RemoveAsteroid(this);
}
