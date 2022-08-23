#pragma once
#include "MoveComponent.h"

class InputComponent : public MoveComponent
{
public:
	InputComponent(Actor* owner, int updateOrder = 10);

	void ProcessInput(const uint8_t* keyState) override;

	float GetMaxForwardSpeed() const { return mMaxForwardSpeed; }
	float GetMaxAngularSpeed() const { return mMaxAngularSpeed; }
	int GetForwardKey() const { return mForwardKey; }
	int GetBackKey() const { return mBackKey; }
	int GetClockwiseKey() const { return mClockwiseKey; }
	int GetCounterClockwiseKey() const { return mCounterClockwiseKey; }

	void SetMaxForwardSpeed(float speed) { mMaxForwardSpeed = speed; }
	void SetMaxAngularSpeed(float speed) { mMaxAngularSpeed = speed; }
	void SetForwardKey(int key) { mForwardKey = key; }
	void SetBackKey(int key) { mBackKey = key; }
	void SetClockwiseKey(int key) { mClockwiseKey = key; }
	void SetCounterClockwiseKey(int key) { mCounterClockwiseKey = key; }

private:
	// max forward/angular speed
	float mMaxForwardSpeed;
	float mMaxAngularSpeed;
	// keys for forward/back
	int mForwardKey;
	int mBackKey;
	// keys for angular movement
	int mClockwiseKey;
	int mCounterClockwiseKey;
};

