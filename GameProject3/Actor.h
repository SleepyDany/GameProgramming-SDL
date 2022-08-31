#pragma once
#include "Math.h"
#include <vector>

class Game;
class Component;


// Game object model - Hierarchy with components
class Actor
{
public:
	enum State
	{
		EActive = 0,
		EPaused,
		EDead
	};

	Actor(Game* game);
	virtual ~Actor();

	void Update(float deltaTime);
	void UpdateComponents(float deltaTime);
	virtual void UpdateActor(float deltaTime);

	void ProcessInput(const uint8_t* keyState);
	virtual void ActorInput(const uint8_t* keyState);

	// Getters/setters

	void AddComponent(Component* component);
	void RemoveComponent(Component* component);

	Game* GetGame() { return mGame; }
	State GetState() const { return mState; }
	const Vector2& GetPosition() const { return mPosition; }
	float GetScale() const { return mScale; }
	float GetRotation() const { return mRotation; }
	Vector2 GetForward() const { return mForward; }

	void SetState(const State& state) { mState = state; }
	void SetPosition(const Vector2& pos) { mPosition = pos; }
	void SetScale(float scale) { mScale = scale; }
	void SetRotation(float rotation) { mRotation = rotation; }
	void SetForward(const Vector2& forward) { mForward = forward; }

private:
	State mState;

	Vector2 mForward;
	Vector2 mPosition;
	float mScale;
	float mRotation;

	std::vector<Component*> mComponents;
	Game* mGame; // dependency injection approach instead of singleton
};

