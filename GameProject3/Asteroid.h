#pragma once
#include "Actor.h"
#include "CircleComponent.h"

class Asteroid : public Actor
{
public:
	Asteroid(Game* game);

	void UpdateActor(float deltaTime) override;

	Vector2 GetSize() const { return mSize; }
	CircleComponent* GetCircle() const { return mCircle; }

	void SetSize(const Vector2& size) { mSize = size; }

private:
	Vector2 mSize;

	CircleComponent* mCircle;
};
