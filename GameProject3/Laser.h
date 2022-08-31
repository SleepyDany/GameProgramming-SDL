#pragma once

#include "Actor.h"

class CircleComponent;
class Game;

class Laser : public Actor
{
public:
	Laser(Game* game);

	void UpdateActor(float deltaTime) override;

	CircleComponent* GetCircle() const { return mCircle; }

private:

	CircleComponent* mCircle;
};
