#pragma once
#include "SpriteComponent.h"
#include <vector>

class AnimationSpriteComponent : public SpriteComponent
{
public:
	AnimationSpriteComponent(class Actor* owner, int drawOrder = 100);

	void Update(float deltaTime) override;
	void SetAnimationTextures(const std::vector<SDL_Texture*>& textures);

	float GetAnimationFPS() const { return mAnimationFPS; }
	void SetAnimationFPS(float fps) { mAnimationFPS = fps; }

private:
	std::vector<SDL_Texture*> mAnimationTextures;
	float mCurFrame;
	float mAnimationFPS;
};

