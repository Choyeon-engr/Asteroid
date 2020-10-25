#pragma once

#include <cstdint>

#include "Actor.hpp"

class Jet : public Actor
{
public:
    Jet(class Game* game);
    
    void UpdateActor(float deltaTime) override;
    
    void ActorInput(const uint8_t* keyState) override;
    
private:
    float mLaserCooldown;
};
