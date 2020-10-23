#pragma once

#include "Component.hpp"

class MovementComponent : public Component
{
public:
    MovementComponent(Actor* owner, int updateOrder) : Component(owner, updateOrder), mForwardSpeed(0.f), mAngularSpeed(0.f) {}
    
    void Update(float deltaTime) override;
    
    const float GetForwardSpeed() const noexcept    { return mForwardSpeed; }
    void SetForwardSpeed(float forwardSpeed)        { mForwardSpeed = forwardSpeed; }
    
    const float GetAngularSpeed() const noexcept    { return mAngularSpeed; }
    void SetAngularSpeed(float angularSpeed)        { mAngularSpeed = angularSpeed; }
    
private:
    float mForwardSpeed;
    float mAngularSpeed;
};
