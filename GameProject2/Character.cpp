#include "Character.h"
#include "Game.h"
#include "AnimationSpriteComponent.h"
#include <iostream>
#include <filesystem>
#include <regex>


Character::Character(Game* game) :
	Actor(game),
	mHSpeed(0.f),
	mVSpeed(0.f)
{
	asc = new AnimationSpriteComponent(this);
	
	std::regex file_regex("Character[0-1][0-9].png");
	std::string dir = "Assets/";
	std::vector<SDL_Texture*> animation_textures;

	for (auto& p : std::filesystem::directory_iterator(dir))
	{
		if (!std::filesystem::is_regular_file(p.status()))
			continue;

		std::string name = p.path().filename().string();

		if (std::regex_match(name, file_regex))
		{
			std::cout << dir + name << " ";
			animation_textures.emplace_back(game->GetTexture(dir + name));
			//animation_textures.emplace_back(game->GetTexture(dir + name));
		}
	}
	std::vector<Uint32> animation_ranges{ 0, 6, 15, 18 };
	asc->SetAnimationTextures(animation_textures, animation_ranges);
	asc->SetAnimation(0);
}

void Character::UpdateActor(float deltaTime)
{
	Actor::UpdateActor(deltaTime);

	Vector2 pos = GetPosition();
	pos.x += mHSpeed * deltaTime;
	pos.y += mVSpeed * deltaTime;

	SetPosition(pos);
}

void Character::ProcessKeyboard(const uint8_t* state)
{
	mVSpeed = 0.f;
	mHSpeed = 0.f;

	if (state[SDL_SCANCODE_A])
	{
		mHSpeed = -150.f;
		asc->SetAnimation(0);
	}

	if (state[SDL_SCANCODE_D])
	{
		mHSpeed = 150.f;
		asc->SetAnimation(0);
	}

	if (state[SDL_SCANCODE_W])
	{
		mVSpeed = -150.f;
	}

	if (state[SDL_SCANCODE_S])
	{
		mVSpeed = 150.f;
	}

	if (state[SDL_SCANCODE_SPACE])
	{
		asc->SetAnimation(1);
	}

	Uint32 event = SDL_GetMouseState(NULL, NULL);
	if (event == SDL_BUTTON_LEFT)
	{
		asc->SetAnimation(2);
	}
}