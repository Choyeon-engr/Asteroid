#include "SpriteComponent.hpp"
#include "Game.hpp"
#include "Actor.hpp"
#include "Shader.hpp"
#include "CML.hpp"

SpriteComponent::SpriteComponent(Actor* owner, int drawOrder)
: Component(owner, drawOrder), mTexture(nullptr), mDrawOrder(drawOrder), mTxtWidth(0), mTxtHeight(0)
{
    mOwner->GetGame()->AddSprite(this);
}

SpriteComponent::~SpriteComponent()
{
    mOwner->GetGame()->RemoveSprite(this);
}

void SpriteComponent::Draw(Shader* shader)
{
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}

void SpriteComponent::SetTexture(SDL_Texture* texture)
{
    mTexture = texture;
    SDL_QueryTexture(texture, nullptr, nullptr, &mTxtWidth, &mTxtHeight);
}
