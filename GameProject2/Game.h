#pragma once
#include <SDL.h>
#include <vector>
#include <unordered_map>
#include <string>

class Game
{
public:
	bool Initialize();
	void RunLoop();
	void Shutdown();

	void AddActor(class Actor* actor);
	void RemoveActor(class Actor* actor);

	void AddSprite(class SpriteComponent* sprite);
	void RemoveSprite(class SpriteComponent* sprite);

	SDL_Texture* GetTexture(const std::string& fileName);

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

	std::vector<class SpriteComponent*> mSprites;

	std::unordered_map<std::string, SDL_Texture*> mTextures;

	bool mIsRunning;
};

