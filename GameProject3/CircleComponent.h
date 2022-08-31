#pragma once
#include "Component.h"

class Actor;

class CircleComponent : public Component
{
public:
	CircleComponent(Actor* owner);

	void SetRadius(float radius) { mRadius = radius; }

	float GetRadius() const { return mRadius; }

	const Vector2& GetCenter() const;

private:

	float mRadius;
};

bool Intersect(const CircleComponent& circle1, const CircleComponent& circle2);
