#include "MovementComponent.hpp"
#include "Actor.hpp"

void MovementComponent::Update(float deltaTime)
{
    mAcceleration = mForce / mMass;
    mForce = Vector2D(0.f, 0.f);
    mVelocity += mAcceleration * deltaTime;
    
    if (!Math::CloseToZero(Math::Sqrt(mVelocity.LengthSquared())))
    {
        Vector2D position = mOwner->GetPosition();
        position += mVelocity * deltaTime;
        
        /* Specialization for Asteroid */
        if (mOwner->GetKinds() == Actor::EJet)
        {
            if (position.x < 0.f)
                position.x = 0.f;
            else if (position.x > 512.f)
                position.x = 512.f;
            
            if (position.y < 0.f)
                position.y = 0.f;
            else if (position.y > 512.f)
                position.y = 512.f;
        }
        
        else if (mOwner->GetKinds() == Actor::EAsteroid)
        {
            if (position.x < 0.f)
                position.x = 512.f;
            else if (position.x > 512.f)
                position.x = 0.f;
            
            if (position.y < 0.f)
                position.y = 512.f;
            else if (position.y > 512.f)
                position.y = 0.f;
        }
        
        mOwner->SetPosition(position);
    }
    
    mVelocity = Vector2D(0.f, 0.f);
    
    if (!Math::CloseToZero(mAngularSpeed))
    {
        float rotation = mOwner->GetRotation();
        rotation += mAngularSpeed * deltaTime;
        mOwner->SetRotation(rotation);
    }
}
