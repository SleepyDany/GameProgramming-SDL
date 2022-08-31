#include "Ship.h"
#include "Laser.h"
#include "Game.h"
#include "AnimationSpriteComponent.h"
#include "InputComponent.h"

Ship::Ship(Game* game) : 
	Actor(game),
	mLaserCountdown(0.0f)
{
	AnimationSpriteComponent* asc = new AnimationSpriteComponent(this);
	std::vector<SDL_Texture*> animation_textures = {
		game->GetTexture("Assets/Ship01.png"),
		game->GetTexture("Assets/Ship02.png"),
		game->GetTexture("Assets/Ship03.png"),
		game->GetTexture("Assets/Ship04.png")
	};
	asc->SetAnimationTextures(animation_textures, {}, true);

	mInput = new InputComponent(this);
	mInput->SetForwardKey(SDL_SCANCODE_D);
	mInput->SetBackKey(SDL_SCANCODE_A);
	mInput->SetClockwiseKey(SDL_SCANCODE_W);
	mInput->SetCounterClockwiseKey(SDL_SCANCODE_S);
	mInput->SetMaxForwardSpeed(200.f);
	mInput->SetMaxAngularSpeed(Math::Pi / 2);
}

void Ship::ActorInput(const uint8_t* keyState)
{
	if (keyState[SDL_SCANCODE_SPACE] && mLaserCountdown <= 0.0f)
	{
		Laser* laser = new Laser(GetGame());

		laser->SetForward(GetForward());
		laser->SetRotation(GetRotation());
		laser->SetPosition(GetPosition() + GetForward() * 60.f);

		mLaserCountdown = 0.5f;
	}
}

void Ship::UpdateActor(float deltaTime)
{
	Actor::UpdateActor(deltaTime);

	mLaserCountdown -= deltaTime;

	// Реализовать интуитивное управление при повороте корабля
}
