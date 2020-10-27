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
    SetKinds(EAsteroid);
    
    CML::Vector2D randomPosition = CML::Random::GetRandomVector2D(CML::Vector2D(0.f, 0.f), CML::Vector2D(512.f, 512.f));
    SetPosition(randomPosition);
    
    SetRotation(CML::Random::GetRandomFloat(0.f, CML::Pi * 2.f));
    
    mMovement = new MovementComponent(this, 2);
    mMovement->AddForce(CML::Vector2D(GetForwardVector().X * 1000.f, GetForwardVector().Y * 1000.f));
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
    mMovement->AddForce(CML::Vector2D(GetForwardVector().X * 800.f, GetForwardVector().Y * 800.f));
}
