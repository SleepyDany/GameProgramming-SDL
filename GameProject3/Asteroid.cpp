#include "Asteroid.h"
#include "Math.h"
#include "Random.h"
#include "SpriteComponent.h"
#include "MoveComponent.h"

Asteroid::Asteroid(Game* game) :
	Actor(game)
{
	Vector2 random_pos = Random::GetVector(Vector2::Zero, Vector2(1024.f, 768.f));
	SetPosition(random_pos);
	SetRotation(Random::GetFloatRange(0.f, Math::TwoPi));
	SetForward(Vector2(Math::Cos(GetRotation()), -Math::Sin(GetRotation())));

	SpriteComponent* sprite = new SpriteComponent(this);
	SDL_Texture* texture = game->GetTexture("Assets/Asteroid.png");
	int w, h;
	SDL_QueryTexture(texture, NULL, NULL, &w, &h);
	sprite->SetTexture(texture);
	mSize = Vector2{ static_cast<float>(w), static_cast<float>(h) };

	MoveComponent* move = new MoveComponent(this);
	move->SetForwardSpeed(Random::GetFloatRange(100.f, 200.f));
	move->SetAngularSpeed(Random::GetFloatRange(0.f, 10.f));

	mCircle = new CircleComponent(this);
	mCircle->SetRadius(40.0f);
}

void Asteroid::UpdateActor(float deltaTime)
{
	auto position = GetPosition();
	auto size = GetSize();
	float rotation = GetRotation();	
	
	if (position.x - mSize.x / 2 > 1024 || position.x + mSize.x / 2 < 0 || position.y + mSize.y / 2 < 0 || position.y - mSize.y / 2 > 768)
	{
		Vector2 random_pos = Random::GetVector(Vector2::Zero, Vector2(1024.f, 768.f));
		SetPosition(random_pos);
		rotation = Random::GetFloatRange(0.f, Math::TwoPi);

		SetPosition(position);
		SetRotation(rotation);
		SetForward(Vector2(Math::Cos(rotation), -Math::Sin(rotation)));
	}
}
