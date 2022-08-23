#include "Game.h"
#include "SDL_image.h"
#include <algorithm>
#include "Actor.h"
#include "SpriteComponent.h"
#include "AnimationSpriteComponent.h"
#include "BGSpriteComponent.h"
#include "Ship.h"
#include "Asteroid.h"
#include "Random.h"

bool Game::Initialize()
{
	mTicksCount = 0;
	mIsRunning = true;

	mWindow = nullptr;
	mRenderer = nullptr;

	int sdlResult = SDL_Init(SDL_INIT_VIDEO);
	if (sdlResult != 0)
	{
		SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
		return false;
	}

	mWindow = SDL_CreateWindow("Game 2", 100, 100, 1024, 768, 0);
	if (!mWindow)
	{
		SDL_Log("Failed to create window: %s", SDL_GetError());
		return false;
	}

	mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (!mRenderer)
	{
		SDL_Log("Failed to create renderer: %s", SDL_GetError());
		return false;
	}


	if (IMG_Init(IMG_INIT_PNG) == 0)
	{
		SDL_Log("Unable to initialize image PNG format: %s", SDL_GetError());
		return false;
	}

	LoadData();

	mTicksCount = SDL_GetTicks();

	return true;
}

void Game::Shutdown()
{
	UnloadData();
	IMG_Quit();

	SDL_DestroyWindow(mWindow);
	SDL_DestroyRenderer(mRenderer);
	SDL_Quit();
}

void Game::RunLoop()
{
	while (mIsRunning)
	{
		ProcessInput();
		UpdateGame();
		GenerateOutput();
	}
}

void Game::ProcessInput()
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

	const Uint8* kb_state = SDL_GetKeyboardState(NULL);
	if (kb_state[SDL_SCANCODE_ESCAPE])
	{
		mIsRunning = false;
	}

	mUpdatingActors = true;
	for (auto& actor : mActors)
	{
		actor->ProcessInput(kb_state);
	}
	mUpdatingActors = false;


	//reinterpret_cast<Ship*>(mActors[0])->ProcessKeyboard(kb_state);
	//reinterpret_cast<Character*>(mActors[1])->ProcessKeyboard(kb_state);
}

void Game::UpdateGame()
{
	while (!SDL_TICKS_PASSED(SDL_GetTicks(), mTicksCount + 16))
		;

	float deltaTime = (SDL_GetTicks() - mTicksCount) / 1000.f;
	mTicksCount = SDL_GetTicks();

	if (deltaTime > 0.05f)
		deltaTime = 0.05f;

	mUpdatingActors = true;
	for (auto& actor : mActors)
	{
		actor->Update(deltaTime);
	}
	mUpdatingActors = false;

	for (auto& pending_actor : mPendingActors)
	{
		mActors.emplace_back(pending_actor);
	}
	mPendingActors.clear();

	std::vector<Actor*> deadActors;
	for (auto& actor : mActors)
	{
		if (actor->GetState() == Actor::EDead)
		{
			deadActors.emplace_back(actor);
		}
	}

	for (auto& actor : deadActors)
	{
		delete actor;
	}
}

void Game::GenerateOutput()
{
	SDL_SetRenderDrawColor(mRenderer, 255, 255, 255, 255);
	SDL_RenderClear(mRenderer);

	for (auto& sprite : mSprites)
	{
		sprite->Draw(mRenderer);
	}

	SDL_RenderPresent(mRenderer);
}

void Game::AddActor(Actor* actor)
{
	if (mUpdatingActors)
	{
		mPendingActors.emplace_back(actor);
	}
	else
	{
		mActors.emplace_back(actor);
	}
}

void Game::RemoveActor(Actor* actor)
{
	auto iter = std::find(mPendingActors.begin(), mPendingActors.end(), actor);
	if (iter != mPendingActors.end())
	{
		std::iter_swap(iter, mPendingActors.end() - 1);
		mPendingActors.pop_back();
	}

	iter = std::find(mActors.begin(), mActors.end(), actor);
	if (iter != mActors.end())
	{
		std::iter_swap(iter, mActors.end() - 1);
		mActors.pop_back();
	}
}

void Game::AddSprite(SpriteComponent* sprite)
{
	int myDrawOrder = sprite->GetDrawOrder();
	auto iter = mSprites.begin();

	for (; iter != mSprites.end(); ++iter)
	{
		if (myDrawOrder < (*iter)->GetDrawOrder())
			break;
	}

	mSprites.insert(iter, sprite);
}

void Game::RemoveSprite(SpriteComponent* sprite)
{
	auto iter = std::find(mSprites.begin(), mSprites.end(), sprite);
	if (iter != mSprites.end())
	{
		mSprites.erase(iter, iter + 1);
	}
}

SDL_Texture* Game::GetTexture(const std::string& fileName)
{
	SDL_Texture* texture = nullptr;
	auto iter = mTextures.find(fileName);
	if (iter != mTextures.end())
	{
		texture = iter->second;
	}
	else
	{
		SDL_Surface* surface = IMG_Load(fileName.c_str());
		if (!surface)
		{
			SDL_Log("Failed to load texture file: %s", fileName.c_str());
			return nullptr;
		}

		texture = SDL_CreateTextureFromSurface(mRenderer, surface);
		SDL_FreeSurface(surface);
		if (!texture)
		{
			SDL_Log("Failed to convert surface to texture: %s", fileName.c_str());
			return nullptr;
		}

		mTextures.emplace(fileName.c_str(), texture);
	}

	return texture;
}

void Game::LoadData()
{
	Ship* ship = new Ship(this);
	ship->SetPosition(Vector2(100.f, 384.f));
	ship->SetScale(1.5f);

	//Character* person = new Character(this);
	//person->SetPosition(Vector2(100.f, 650.f));
	//person->SetScale(1.f);

	Actor* background = new Actor(this);
	background->SetPosition(Vector2(512.f, 384.f));

	//TileMapComponent* tile_sc = new TileMapComponent(background, 3);
	//tile_sc->Load("Assets/Tiles.tsx");

	//TileMapComponent* tile_sc1 = new TileMapComponent(background, 2);
	//tile_sc1->Load("Assets/Tiles1.tsx");

	//TileMapComponent* tile_sc2 = new TileMapComponent(background, 1);
	//tile_sc2->Load("Assets/Tiles2.tsx");

	BGSpriteComponent* background_sc = new BGSpriteComponent(background);
	background_sc->SetScreenSize(Vector2(1024.f, 768.f));
	std::vector<SDL_Texture*> background_textures = {
		GetTexture("Assets/Farback01.png"),
		GetTexture("Assets/Farback02.png")
	};
	background_sc->SetBGTextures(background_textures);
	background_sc->SetScreenScrollSpeed(-10.f);


	BGSpriteComponent* stars_sc = new BGSpriteComponent(background, 50);
	stars_sc->SetScreenScrollSpeed(-25.f);
	stars_sc->SetScreenSize(Vector2(1024.f, 768.f));
	std::vector<SDL_Texture*> stars_textures = { 
		GetTexture("Assets/Stars.png"),
		GetTexture("Assets/Stars.png")
	};
	stars_sc->SetBGTextures(stars_textures);

	const int numAsteroids = Random::GetIntRange(8, 15);
	for (int i = 0; i < numAsteroids; ++i)
	{
		new Asteroid(this);
	}
}

void Game::UnloadData()
{
	while (!mActors.empty())
	{
		delete mActors.back();
	}

	for (auto& texture : mTextures)
	{
		SDL_DestroyTexture(texture.second);
	}
	mTextures.clear();
}


