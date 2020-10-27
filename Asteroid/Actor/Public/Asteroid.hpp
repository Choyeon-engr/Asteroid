#pragma once

#include "Actor.hpp"

class Asteroid : public Actor
{
public:
    Asteroid(class Game* game);
    ~Asteroid();
    
    void UpdateActor(float deltaTime) override;
    
    class CircleComponent* GetCircle() { return mCircle; }
    
private:
    class MovementComponent* mMovement;
    class CircleComponent* mCircle;
};
