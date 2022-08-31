#include "CircleComponent.h"

CircleComponent::CircleComponent(Actor* owner) :
	Component(owner),
	mRadius(0)
{
}

const Vector2& CircleComponent::GetCenter() const
{
	return mOwner->GetPosition(); // ?
}

bool Intersect(const CircleComponent& circle1, const CircleComponent& circle2)
{
	const Vector2 diff = circle1.GetCenter() - circle2.GetCenter();
	const float cur_dist_sq = diff.LengthSq();

	float intersect_dist_sq = circle1.GetRadius() + circle2.GetRadius();
	intersect_dist_sq *= intersect_dist_sq;

	return cur_dist_sq <= intersect_dist_sq;
}
