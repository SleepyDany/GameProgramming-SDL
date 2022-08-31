#pragma once
#include <SDL.h>
#include <vector>
#include <unordered_map>
#include <string>

class Actor;
class SpriteComponent;
class Asteroid;

class Game
{
public:
	bool Initialize();
	void RunLoop();
	void Shutdown();

	void AddActor(Actor* actor);
	void RemoveActor(Actor* actor);

	void AddSprite(SpriteComponent* sprite);
	void RemoveSprite(SpriteComponent* sprite);

	SDL_Texture* GetTexture(const std::string& fileName);
	std::vector<Asteroid*> GetAsteroids() const { return mAsteroids; }

private:
	void ProcessInput();
	void UpdateGame();
	void GenerateOutput();

	void LoadData();
	void UnloadData();


	Uint32 mTicksCount;

	SDL_Window* mWindow;
	SDL_Renderer* mRenderer;

	// Active actors
	std::vector<Actor*> mActors;
	// Pending actors
	std::vector<Actor*> mPendingActors;
	bool mUpdatingActors;

	std::vector<SpriteComponent*> mSprites;

	std::unordered_map<std::string, SDL_Texture*> mTextures;

	std::vector<Asteroid*> mAsteroids;

	bool mIsRunning;
};

