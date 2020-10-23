#pragma once

#include "Component.hpp"
#include "CML.hpp"

class CircleComponent : public Component
{
public:
    CircleComponent(class Actor* owner, int updateOrder) : Component(owner, updateOrder), mRadius(0.f) {}
    
    float GetRadius() const         { return mOwner->GetScale() * mRadius; }
    void SetRadius(float radius)    { mRadius = radius; }
    
    const CML::Vector2D& GetCenter() const { return mOwner->GetPosition(); }
    
private:
    float mRadius;
};

bool Intersect(const CircleComponent& a, const CircleComponent& b)
{
    CML::Vector2D d = a.GetCenter() - b.GetCenter();
    float dSquared = d.LengthSquared();
    
    float rSquared = a.GetRadius() + a.GetRadius();
    rSquared *= rSquared;
    
    return dSquared <= rSquared;
}
