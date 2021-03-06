#pragma once

#include <SDL2/SDL.h>
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

class Game
{
public:
    Game() : mIsRunning(true), mIsUpdatingActors(false), mTicksCount(0), mIsDead(false), mRespawnTime(3.f) {}
    
    bool Init();
    void Loop();
    void Quit();
    
    void AddActor(class Actor* actor);
    void RemoveActor(class Actor* actor);
    
    void AddSprite(class SpriteComponent* sprite);
    void RemoveSprite(class SpriteComponent* sprite);
    
    SDL_Texture* GetTexture(const string& fileName);
    
    /* Specialization for Asteroid */
    void AddAsteroid(class Asteroid* asteroid);
    void RemoveAsteroid(class Asteroid* asteroid);
    const vector<class Asteroid*>& GetAsteroids() const noexcept { return mAsteroids; }
    
    void SetIsDead(bool isDead) { mIsDead = isDead; }
    
private:
    void Input();
    void Update();
    void Output();
    
    void LoadData();
    void UnloadData();
    
    bool LoadShaders();
    void InitSpriteVerts();
    
    bool mIsRunning;
    bool mIsUpdatingActors;
    
    Uint32 mTicksCount;
    
    SDL_Window* mWindow;
    SDL_GLContext mContext;
    
    vector<class Actor*> mActors;
    vector<class Actor*> mPendingActors;
    
    vector<class SpriteComponent*> mSprites;
    unordered_map<string, SDL_Texture*> mTextures;
    
    class Shader* mSpriteShader;
    class VertexArray* mSpriteVerts;
    
    /* Specialization for Asteroid */
    class Jet* mJet;
    vector<class Asteroid*> mAsteroids;
    
    bool mIsDead;
    float mRespawnTime;
};
