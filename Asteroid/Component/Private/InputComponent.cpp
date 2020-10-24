#include "InputComponent.hpp"

void InputComponent::Input(const uint8_t* keyState)
{
    float forwardSpeed = 0.f;
    
    if (keyState[mForwardKey])
        forwardSpeed += mMaxForwardSpeed;
    
    if (keyState[mBackwardKey])
        forwardSpeed -= mMaxForwardSpeed;
    
    SetForwardSpeed(forwardSpeed);
    
    float angularSpeed = 0.f;
    
    if (keyState[mClockwiseKey])
        angularSpeed += mMaxAngularSpeed;
    
    if (keyState[mCounterClockwiseKey])
        angularSpeed -= mMaxAngularSpeed;
    
    SetAngularSpeed(angularSpeed);
}
