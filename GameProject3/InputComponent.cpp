#include "InputComponent.h"

InputComponent::InputComponent(Actor* owner, int updateOrder) : 
	MoveComponent(owner, updateOrder),
	mMaxForwardSpeed(0.f),
	mMaxAngularSpeed(0.f),
	mForwardKey(0),
	mBackKey(0),
	mClockwiseKey(0),
	mCounterClockwiseKey(0)
{
}

void InputComponent::ProcessInput(const uint8_t* keyState)
{
	float forward_speed = 0.f;

	if (keyState[mForwardKey])
	{
		forward_speed += mMaxForwardSpeed;
	}

	if (keyState[mBackKey])
	{
		forward_speed -= mMaxForwardSpeed;
	}
	SetForwardSpeed(forward_speed);

	float angular_speed = 0.f;
	
	if (keyState[mClockwiseKey])
	{
		angular_speed += mMaxAngularSpeed;
	}

	if (keyState[mCounterClockwiseKey])
	{
		angular_speed -= mMaxAngularSpeed;
	}
	SetAngularSpeed(angular_speed);
}
