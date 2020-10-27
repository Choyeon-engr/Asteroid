#include <cmath>

#include "MovementComponent.hpp"
#include "Actor.hpp"

void MovementComponent::Update(float deltaTime)
{
    mAcceleration = mForce / mMass;
    mForce = CML::Vector2D(0.f, 0.f);
    mVelocity += mAcceleration * deltaTime;
    
    if (!CML::CloseToZero(sqrt(mVelocity.LengthSquared())))
    {
        CML::Vector2D position = mOwner->GetPosition();
        position += mVelocity * deltaTime;
        
        /* Specialization for Asteroid */
        if (mOwner->GetKinds() == Actor::EJet)
        {
            if (position.X < 0.f)
                position.X = 0.f;
            else if (position.X > 512.f)
                position.X = 512.f;
            
            if (position.Y < 0.f)
                position.Y = 0.f;
            else if (position.Y > 512.f)
                position.Y = 512.f;
        }
        
        else if (mOwner->GetKinds() == Actor::EAsteroid)
        {
            if (position.X < 0.f)
                position.X = 512.f;
            else if (position.X > 512.f)
                position.X = 0.f;
            
            if (position.Y < 0.f)
                position.Y = 512.f;
            else if (position.Y > 512.f)
                position.Y = 0.f;
        }
        
        mOwner->SetPosition(position);
    }
    
    mVelocity = CML::Vector2D(0.f, 0.f);
    
    if (!CML::CloseToZero(mAngularSpeed))
    {
        float rotation = mOwner->GetRotation();
        rotation += mAngularSpeed * deltaTime;
        mOwner->SetRotation(rotation);
    }
}
