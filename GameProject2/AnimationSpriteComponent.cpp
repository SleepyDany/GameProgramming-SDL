#include "AnimationSpriteComponent.h"
//#include "Actor.h"

AnimationSpriteComponent::AnimationSpriteComponent(Actor* owner, int drawOrder) : 
	SpriteComponent(owner, drawOrder),
	mCurFrame(0.f),
	mAnimationFPS(24.f)
{
}

void AnimationSpriteComponent::Update(float deltaTime)
{
	SpriteComponent::Update(deltaTime);

	if (mAnimationTextures.size() > 0)
	{
		mCurFrame += mAnimationFPS * deltaTime;

		while (mCurFrame >= mAnimationTextures.size())
		{
			mCurFrame -= mAnimationTextures.size();
		}

		SetTexture(mAnimationTextures[static_cast<int>(mCurFrame)]);
	}
}

void AnimationSpriteComponent::SetAnimationTextures(const std::vector<SDL_Texture*>& textures)
{
	mAnimationTextures = textures;
	
	if (mAnimationTextures.size() > 0)
	{
		mCurFrame = 0;
		SetTexture(mAnimationTextures[0]);
	}
}
