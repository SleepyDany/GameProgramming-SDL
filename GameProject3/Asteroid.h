#pragma once
#include "Actor.h"

class Asteroid : public Actor
{
public:
	Asteroid(Game* game);

	void UpdateActor(float deltaTime) override;

	Vector2 GetSize() const { return mSize; }

	void SetSize(const Vector2& size) { mSize = size; }

private:
	Vector2 mSize;
};
