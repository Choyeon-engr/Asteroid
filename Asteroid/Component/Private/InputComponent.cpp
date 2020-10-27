#include "InputComponent.hpp"
#include "Actor.hpp"

void InputComponent::Input(const uint8_t* keyState)
{
    CML::Vector2D force(0.f, 0.f);
    
    if (keyState[mForwardKey])
        force += mOwner->GetForwardVector() * mMaxForceScalar;
    
    if (keyState[mBackwardKey])
        force -= mOwner->GetForwardVector() * mMaxForceScalar;
    
    AddForce(force);
    
    float angularSpeed = 0.f;
    
    if (keyState[mClockwiseKey])
        angularSpeed += mMaxAngularSpeed;
    
    if (keyState[mCounterClockwiseKey])
        angularSpeed -= mMaxAngularSpeed;
    
    SetAngularSpeed(angularSpeed);
}
