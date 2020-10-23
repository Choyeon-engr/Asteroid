#include <string>

#include "Asteroid.hpp"
#include "Game.hpp"
#include "SpriteComponent.hpp"
#include "MovementComponent.hpp"
#include "CircleComponent.hpp"
#include "CML.hpp"

Asteroid::Asteroid(Game* game)
    : Actor(game), mCircle(nullptr)
{
    CML::Vector2D randomPosition = CML::Random::GetRandomVector2D(CML::Vector2D(0.f, 0.f), CML::Vector2D(512.f, 512.f));
    SetPosition(randomPosition);
    
    SetRotation(CML::Random::GetRandomFloat(0.f, CML::Pi * 2.f));
    
    SpriteComponent* sprite = new SpriteComponent(this, 2);
    sprite->SetTexture(game->GetTexture("/Assets/Asteroid.png"));
    game->AddSprite(sprite);
    
    MovementComponent* movement = new MovementComponent(this, 1);
    movement->SetForwardSpeed(100.f);
    
    mCircle = new CircleComponent(this, 3);
    mCircle->SetRadius(30.f);
    
    game->AddAsteroid(this);
}

Asteroid::~Asteroid()
{
    GetGame()->RemoveAsteroid(this);
}
