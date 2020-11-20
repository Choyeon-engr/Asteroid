#include "CircleComponent.hpp"

bool Intersect(const CircleComponent& a, const CircleComponent& b)
{
    Vector2D d = a.GetCenter() - b.GetCenter();
    float dSquared = d.LengthSquared();
    
    float rSquared = a.GetRadius() + a.GetRadius();
    rSquared *= rSquared;
    
    return dSquared <= rSquared;
}
