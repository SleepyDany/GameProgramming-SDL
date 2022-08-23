#include "MoveComponent.h"

MoveComponent::MoveComponent(Actor* owner, int updateOrder) :
	Component(owner, updateOrder),
	mAngularSpeed(0.f),
	mForwardSpeed(0.f)
{
}

void MoveComponent::Update(float deltaTime)
{
	if (!Math::NearZero(mAngularSpeed))
	{
		float rotation = mOwner->GetRotation();
		rotation += mAngularSpeed * deltaTime;
		mOwner->SetRotation(rotation);
	}

	if (!Math::NearZero(mForwardSpeed))
	{
		Vector2 position = mOwner->GetPosition();
		position += mOwner->GetForward() * mForwardSpeed * deltaTime;
		mOwner->SetPosition(position);
	}
}