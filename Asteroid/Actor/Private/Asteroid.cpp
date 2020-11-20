#include <string>

#include "Asteroid.hpp"
#include "Game.hpp"
#include "MovementComponent.hpp"
#include "SpriteComponent.hpp"
#include "CircleComponent.hpp"

Asteroid::Asteroid(Game* game)
: Actor(game)
{
    SetKinds(EAsteroid);
    
    Vector2D randomPosition = Random::GetRandomVector2D(Vector2D(0.f, 0.f), Vector2D(512.f, 512.f));
    SetPosition(randomPosition);
    
    SetRotation(Random::GetRandomFloat(0.f, Math::Pi * 2.f));
    
    mMovement = new MovementComponent(this, 2);
    mMovement->AddForce(Vector2D(GetForwardVector().x * 1000.f, GetForwardVector().y * 1000.f));
    mMovement->SetMass(1.f);
    
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

void Asteroid::UpdateActor(float deltaTime)
{
    mMovement->AddForce(Vector2D(GetForwardVector().x * 800.f, GetForwardVector().y * 800.f));
}
