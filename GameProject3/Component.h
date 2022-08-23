#pragma once
#include "Actor.h"

class Component
{
public:
	Component(Actor* owner, int updateOrder = 100);
	virtual ~Component();

	virtual void Update(float deltaTime);
	int GetUpdateOrder() const { return mUpdateOrder; }

	virtual void ProcessInput(const uint8_t* keyState) {};

protected:
	Actor* mOwner;
	int mUpdateOrder;
};

