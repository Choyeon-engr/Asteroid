#include <SDL2_image/SDL_image.h>
#include "Game.hpp"
#include "Actor.hpp"
#include "SpriteComponent.hpp"

bool Game::Init()
{
    if (SDL_Init(SDL_INIT_VIDEO))
        return false;
    
    mWindow = SDL_CreateWindow("Asteroid", 0, 0, 512, 512, 0);
    if (!mWindow)
        return false;
    
    mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!mRenderer)
        return false;
    
    return true;
}

void Game::Loop()
{
    while (mIsRunning)
    {
        Input();
        Update();
        Output();
    }
}

void Game::Quit()
{
    SDL_DestroyRenderer(mRenderer);
    SDL_DestroyWindow(mWindow);
    SDL_Quit();
}

void Game::AddActor(Actor* actor)
{
    if (mIsUpdatingActors)
        mPendingActors.emplace_back(actor);
    else
        mActors.emplace_back(actor);
}

void Game::RemoveActor(Actor* actor)
{
    auto iter = find(mPendingActors.begin(), mPendingActors.end(), actor);
    if (iter != mPendingActors.end())
    {
        iter_swap(iter, mPendingActors.end() - 1);
        mPendingActors.pop_back();
        return;
    }
    
    iter = find(mActors.begin(), mActors.end(), actor);
    if (iter != mActors.end())
    {
        iter_swap(iter, mActors.end() - 1);
        mActors.pop_back();
    }
}

void Game::AddSprite(SpriteComponent* sprite)
{
    int drawOrder = sprite->GetDrawOrder();
    auto iter = mSprites.begin();
    
    for (; iter != mSprites.end(); ++iter)
        if (drawOrder < (*iter)->GetDrawOrder())
            break;
    
    mSprites.insert(iter, sprite);
}

void Game::RemoveSprite(SpriteComponent* sprite)
{
    auto iter = find(mSprites.begin(), mSprites.end(), sprite);
    mSprites.erase(iter);
}

SDL_Texture* Game::GetTexture(string& fileName)
{
    SDL_Texture* texture = nullptr;
    auto iter = mTextures.find(fileName);
    
    if (iter != mTextures.end())
        texture = iter->second;
    else
    {
        SDL_Surface* surface = IMG_Load(fileName.c_str());
        if (!surface)
            return nullptr;
        
        texture = SDL_CreateTextureFromSurface(mRenderer, surface);
        SDL_free(surface);
        if (!texture)
            return nullptr;
        
        mTextures.emplace(fileName.c_str(), texture);
    }
    
    return texture;
}

void Game::Input()
{
    SDL_Event event;
    
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
            case SDL_QUIT:
                mIsRunning = false;
                break;
        }
    }
}

void Game::Update()
{
    while (!SDL_TICKS_PASSED(SDL_GetTicks(), mTicksCount + 16));
    
    float deltaTime = (SDL_GetTicks() - mTicksCount) / 1000.f;
    if (deltaTime > 0.05f)
        deltaTime = 0.05f;
    
    mTicksCount = SDL_GetTicks();
}

void Game::Output()
{
    SDL_SetRenderDrawColor(mRenderer, 0, 50, 100, 255);
    SDL_RenderClear(mRenderer);
    
    SDL_RenderPresent(mRenderer);
}
