#pragma once

#include <cstdint>

#include "MovementComponent.hpp"
#include "CML.hpp"

class InputComponent : public MovementComponent
{
public:
    InputComponent(class Actor* owner, int updateOrder) : MovementComponent(owner, updateOrder), mMaxForceScalar(0.f), mMaxAngularSpeed(0.f), mForwardKey(0), mBackwardKey(0), mClockwiseKey(0), mCounterClockwiseKey(0) {}
    
    void Input(const uint8_t* keyState) override;
    
    float GetMaxForceScalar() const noexcept    { return mMaxForceScalar; }
    void SetMaxForceScalar(float forceScalar)   { mMaxForceScalar = forceScalar; }
    
    float GetMaxAngularSpeed() const noexcept       { return mMaxAngularSpeed; }
    void SetMaxAngularSpeed(float maxAngularSpeed)  { mMaxAngularSpeed = maxAngularSpeed; }
    
    int GetForwardKey() const noexcept  { return mForwardKey; }
    void SetForwardKey(int forwardKey)  { mForwardKey = forwardKey; }
    
    int GetBackwardKey() const noexcept     { return mBackwardKey; }
    void SetBackwardKey(int backwardKey)    { mBackwardKey = backwardKey; }
    
    int GetClockwiseKey() const noexcept    { return mClockwiseKey; }
    void SetClockwiseKey(int clockwiseKey)  { mClockwiseKey = clockwiseKey; }
    
    int GetCounterClockwiseKey() const noexcept             { return mCounterClockwiseKey; }
    void SetCounterClockwiseKey(int counterClockwiseKey)    { mCounterClockwiseKey = counterClockwiseKey; }
    
private:
    float mMaxForceScalar;
    float mMaxAngularSpeed;
    
    int mForwardKey;
    int mBackwardKey;
    
    int mClockwiseKey;
    int mCounterClockwiseKey;
};
