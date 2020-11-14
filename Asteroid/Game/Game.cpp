#include <SDL2_image/SDL_image.h>
#include <GL/glew.h>

#include "Game.hpp"
#include "Actor.hpp"
#include "SpriteComponent.hpp"
#include "Jet.hpp"
#include "Asteroid.hpp"
#include "Shader.hpp"
#include "VertexArray.hpp"
#include "CML.hpp"

bool Game::Init()
{
    if (SDL_Init(SDL_INIT_VIDEO))
        return false;
    
    if (!IMG_Init(IMG_INIT_PNG))
        return false;
    
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
    
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
    
    mWindow = SDL_CreateWindow("Asteroid", 0, 0, 512, 512, SDL_WINDOW_OPENGL);
    if (!mWindow)
        return false;
    
    mContext = SDL_GL_CreateContext(mWindow);
    
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK)
        return false;
    
    glGetError();
    
    if (!LoadShaders())
        return false;
    
    InitSpriteVertices();
    
    CML::Random::Init();
    
    LoadData();
    
    mTicksCount = SDL_GetTicks();
    
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
    UnloadData();
    IMG_Quit();
    SDL_GL_DeleteContext(mContext);
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

SDL_Texture* Game::GetTexture(const string& fileName)
{
    SDL_Texture* texture = nullptr;
    const string absolutePath = string("/Users/choyeon/Game/Asteroid/Asteroid") + fileName;
    auto iter = mTextures.find(absolutePath.c_str());
    
    if (iter != mTextures.end())
        texture = iter->second;
    else
    {
        SDL_Surface* surface = IMG_Load(absolutePath.c_str());
        if (!surface)
            return nullptr;
        
        // texture = SDL_CreateTextureFromSurface(mRenderer, surface);
        SDL_free(surface);
        if (!texture)
            return nullptr;
        
        mTextures.emplace(absolutePath, texture);
    }
    
    return texture;
}

void Game::AddAsteroid(Asteroid* asteroid)
{
    mAsteroids.emplace_back(asteroid);
}

void Game::RemoveAsteroid(Asteroid* asteroid)
{
    auto iter = find(mAsteroids.begin(), mAsteroids.end(), asteroid);
    if (iter != mAsteroids.end())
        mAsteroids.erase(iter);
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
    
    const Uint8* keyState = SDL_GetKeyboardState(nullptr);
    mIsUpdatingActors = true;
    for (auto actor : mActors)
        actor->Input(keyState);
    mIsUpdatingActors = false;
}

void Game::Update()
{
    while (!SDL_TICKS_PASSED(SDL_GetTicks(), mTicksCount + 16));
    
    float deltaTime = (SDL_GetTicks() - mTicksCount) / 1000.f;
    if (deltaTime > 0.05f)
        deltaTime = 0.05f;
    
    mTicksCount = SDL_GetTicks();
    
    mIsUpdatingActors = true;
    for (auto actor : mActors)
        actor->Update(deltaTime);
    mIsUpdatingActors = false;
    
    for (auto pendingActor : mPendingActors)
        mActors.emplace_back(pendingActor);
    mPendingActors.clear();
    
    vector<Actor*> disabledActors;
    for (auto actor : mActors)
        if (actor->GetState() == Actor::EDisable)
            disabledActors.emplace_back(actor);
    
    for (auto disabledActor : disabledActors)
        delete disabledActor;
    
    if (mIsDead)
    {
        if (mRespawnTime <= 0.f)
        {
            mJet = new Jet(this);
            mRespawnTime = 3.f;
            mIsDead = false;
        }
        else
            mRespawnTime -= deltaTime;
    }
}

void Game::Output()
{
    glClearColor(0.86f, 0.86f, 0.86f, 1.f);
    glClear(GL_COLOR_BUFFER_BIT);
    
    mSpriteShader->SetActive();
    mSpriteVertices->SetActive();
    
    for (auto sprite : mSprites)
        sprite->Draw(mSpriteShader);
    
    SDL_GL_SwapWindow(mWindow);
}

void Game::LoadData()
{
    mJet = new Jet(this);
    
    const int AsteroidsCnt = 5;
    for (int i = 0; i < AsteroidsCnt; ++i)
    new Asteroid(this);
}

void Game::UnloadData()
{
    while (!mActors.empty())
        delete mActors.back();
    
    for (auto texture : mTextures)
        SDL_DestroyTexture(texture.second);
    
    mTextures.clear();
}

bool Game::LoadShaders()
{
    mSpriteShader = new Shader();
    if (!mSpriteShader->Load("/Shaders/Basic.vert", "/Shaders/Basic.frag"))
        return false;
    
    mSpriteShader->SetActive();
    
    return true;
}

void Game::InitSpriteVertices()
{
    float vertices[] = {
        -0.5f,  0.5f, 0.f, 0.f, 0.f,
        0.5f,  0.5f, 0.f, 1.f, 0.f,
        0.5f, -0.5f, 0.f, 1.f, 1.f,
        -0.5f, -0.5f, 0.f, 0.f, 1.f
    };
    
    unsigned int indices[] = {
        0, 1, 2,
        2, 3, 0
    };
    
    mSpriteVertices = new VertexArray(vertices, 4, indices, 6);
}
