#pragma once

class Component
{
public:
    Component(class Actor* owner, int updateOrder);
    virtual ~Component();
    
    virtual void Update(float deltaTime);
    
    int GetUpdateOrder() const noexcept { return mUpdateOrder; }
    
protected:
    class Actor* mOwner;
    
    int mUpdateOrder;
};
