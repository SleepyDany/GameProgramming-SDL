#include "Laser.h"
#include "SpriteComponent.h"
#include "CircleComponent.h"
#include "MoveComponent.h"
#include "Asteroid.h"
#include "Game.h"
#include <iostream>

Laser::Laser(Game* game) :
	Actor(game),
	mCircle(nullptr)
{
	mCircle = new CircleComponent(this);
	mCircle->SetRadius(20.f);

	MoveComponent* movement = new MoveComponent(this);
	movement->SetForwardSpeed(400.0f);
	movement->SetAngularSpeed(0.0f);

	SpriteComponent* sprite = new SpriteComponent(this);
	sprite->SetTexture(GetGame()->GetTexture("Assets/Laser.png"));
}

void Laser::UpdateActor(float deltaTime)
{
	const Vector2 position = GetPosition();
	if (position.x < -10 || position.x > 1034 || position.y > 778 || position.y < -10)
	{
		SetState(EDead);
		std::cout << "Laser is dead!";
		return;
	}

	const std::vector<Asteroid*> Asteroids = GetGame()->GetAsteroids();

	for (auto& asteroid : Asteroids)
	{
		if (Intersect(*asteroid->GetCircle(), *mCircle))
		{
			SetState(EDead);
			asteroid->SetState(EDead);

			break;
		}
	}
}
