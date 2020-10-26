#include <SDL2/SDL.h>

#include "Jet.hpp"
#include "Game.hpp"
#include "SpriteComponent.hpp"
#include "InputComponent.hpp"
#include "Laser.hpp"
#include "CML.hpp"

Jet::Jet(Game* game)
    : Actor(game), mLaserCooldown(0.f)
{
    SetPosition(CML::Vector2D(256.f, 256.f));
    SetRotation(CML::Pi / 2.f);
    
    SpriteComponent* sprite = new SpriteComponent(this, 3);
    sprite->SetTexture(game->GetTexture("/Assets/Jet.png"));
    game->AddSprite(sprite);
    
    InputComponent* input = new InputComponent(this, 1);
    input->SetForwardKey(SDL_SCANCODE_W);
    input->SetBackwardKey(SDL_SCANCODE_S);
    input->SetClockwiseKey(SDL_SCANCODE_A);
    input->SetCounterClockwiseKey(SDL_SCANCODE_D);
    input->SetMaxForwardSpeed(300.f);
    input->SetMaxAngularSpeed(CML::Pi * 2);
}

void Jet::UpdateActor(float deltaTime)
{
    mLaserCooldown -= deltaTime;
}

void Jet::ActorInput(const uint8_t* keyState)
{
    if (keyState[SDL_SCANCODE_SPACE] && mLaserCooldown <= 0.f)
    {
        Laser* laser = new Laser(GetGame());
        laser->SetPosition(GetPosition());
        laser->SetRotation(GetRotation());
         
        mLaserCooldown = 0.5f;
    }
}