#include "Actor.h"
#include "Game.h"
#include "Component.h"

Actor::Actor(Game* game) : 
	mGame(game)
{
	mState = State::EActive;

	mScale = 1.0f;
	mPosition = Vector2(0.f, 0.f);
	mRotation = 0.f;
	mForward = Vector2(Math::Cos(mRotation), -Math::Sin(mRotation));

	game->AddActor(this);
}

Actor::~Actor()
{
	mGame->RemoveActor(this);

	while (!mComponents.empty())
	{
		delete mComponents.back();
	}
}

void Actor::Update(float deltaTime)
{
	if (mState == EActive)
	{
		UpdateComponents(deltaTime);
		UpdateActor(deltaTime);
	}
}

void Actor::UpdateComponents(float deltaTime)
{
	for (auto& component : mComponents)
	{
		component->Update(deltaTime);
	}
}

void Actor::UpdateActor(float deltaTime)
{
	mForward = Vector2(Math::Cos(mRotation), -Math::Sin(mRotation));
}

void Actor::ProcessInput(const uint8_t* keyState)
{
	if (mState == EActive)
	{
		for (auto& component : mComponents)
		{
			component->ProcessInput(keyState);
		}
		ActorInput(keyState);
	}
}

void Actor::ActorInput(const uint8_t* keyState)
{
}

void Actor::AddComponent(Component* component)
{
	int insertOrder = component->GetUpdateOrder();
	auto iter = mComponents.begin();

	for (; iter != mComponents.end(); ++iter)
	{
		if (insertOrder < (*iter)->GetUpdateOrder())
			break;
	}

	mComponents.insert(iter, component);
}

void Actor::RemoveComponent(Component* component)
{
	auto iter = std::find(mComponents.begin(), mComponents.end(), component);

	if (iter != mComponents.end())
	{
		mComponents.erase(iter);
	}
}