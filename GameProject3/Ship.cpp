#include "Ship.h"
#include "InputComponent.h"

Ship::Ship(Game* game) : 
	Actor(game),
	mHSpeed(0.f),
	mVSpeed(0.f)
{
	AnimationSpriteComponent* asc = new AnimationSpriteComponent(this);
	std::vector<SDL_Texture*> animation_textures = {
		game->GetTexture("Assets/Ship01.png"),
		game->GetTexture("Assets/Ship02.png"),
		game->GetTexture("Assets/Ship03.png"),
		game->GetTexture("Assets/Ship04.png")
	};
	asc->SetAnimationTextures(animation_textures, {}, true);

	InputComponent* input = new InputComponent(this);
	input->SetForwardKey(SDL_SCANCODE_D);
	input->SetBackKey(SDL_SCANCODE_A);
	input->SetClockwiseKey(SDL_SCANCODE_W);
	input->SetCounterClockwiseKey(SDL_SCANCODE_S);
	input->SetMaxForwardSpeed(200.f);
	input->SetMaxAngularSpeed(Math::Pi / 2);
}

void Ship::UpdateActor(float deltaTime)
{
	Actor::UpdateActor(deltaTime);

	Vector2 pos = GetPosition();
	pos.x += mHSpeed * deltaTime;
	pos.y += mVSpeed * deltaTime;

	SetPosition(pos);
}

//void Ship::ProcessKeyboard(const uint8_t* state)
//{
//	mVSpeed = 0.f;
//	mHSpeed = 0.f;
//	float rotation = 0.f;
//
//	if (state[SDL_SCANCODE_A])
//	{
//		mHSpeed = -150.f;
//		rotation += M_PI;
//	}
//
//	if (state[SDL_SCANCODE_D])
//	{
//		mHSpeed = 150.f;
//	}
//
//	if (state[SDL_SCANCODE_W])
//	{
//		mVSpeed = -150.f;
//		rotation += M_PI / 6 * (mHSpeed >= 0.f ? 1.f : -1.f);
//	}
//
//	if (state[SDL_SCANCODE_S])
//	{
//		mVSpeed = 150.f;
//		rotation -= M_PI / 6 * (mHSpeed >= 0.f ? 1.f : -1.f);
//	}
//
//	SetRotation(rotation);
//}