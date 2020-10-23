#include "MovementComponent.hpp"
#include "Actor.hpp"
#include "CML.hpp"

void MovementComponent::Update(float deltaTime)
{
    if (!CML::CloseToZero(mForwardSpeed))
    {
        CML::Vector2D position = mOwner->GetPosition();
        position += mOwner->GetForwardVector() * mForwardSpeed * deltaTime;
        
        /* Specialization for Asteroid */
        if (position.X < 0.f)
            position.X = 512.f;
        else if (position.X > 512.f)
            position.X = 0.f;
        
        if (position.Y < 0.f)
            position.Y = 512.f;
        else if (position.Y > 512.f)
            position.Y = 0.f;
        
        mOwner->SetPosition(position);
    }
    
    if (!CML::CloseToZero(mAngularSpeed))
    {
        float rotation = mOwner->GetRotation();
        rotation += mAngularSpeed * deltaTime;
        mOwner->SetRotation(rotation);
    }
}
