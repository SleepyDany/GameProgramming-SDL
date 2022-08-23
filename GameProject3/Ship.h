#pragma once
#include "Actor.h"
#include "Game.h"
#include "AnimationSpriteComponent.h"

class Ship : public Actor
{
public:
	Ship(Game* game);

	void UpdateActor(float deltaTime) override;
	//void ProcessKeyboard(const uint8_t* state);

	float GetHSpeed() const { return mHSpeed; }
	float GetVSpeed() const { return mVSpeed; }

private:
	float mHSpeed;
	float mVSpeed;
};

