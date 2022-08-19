#include "AnimationSpriteComponent.h"
#include "Actor.h"

AnimationSpriteComponent::AnimationSpriteComponent(Actor* owner, int drawOrder) :
	SpriteComponent(owner, drawOrder),
	mCurFrame(0.f),
	mAnimationFPS(24.f),
	mCurAnimationId(0),
	mIsLooped(false),
	mIsPlaying(false)
{
}

void AnimationSpriteComponent::Update(float deltaTime)
{
	SpriteComponent::Update(deltaTime);

	if (mAnimationTextures.size() > 0 && mIsPlaying)
	{
		mCurFrame += mAnimationFPS * deltaTime;

		while (mCurFrame >= mAnimationRanges[mCurAnimationId + 1] && mIsPlaying)
		{
			mIsPlaying = mIsLooped;
			mCurFrame = mIsLooped ? mCurFrame - GetAnimationSize(mCurAnimationId) : mAnimationRanges[mCurAnimationId + 1] - 1;
		}

		SetTexture(mAnimationTextures[static_cast<int>(mCurFrame)]);
	}
}

void AnimationSpriteComponent::SetAnimationTextures(const std::vector<SDL_Texture*>& textures,
													const std::vector<Uint32>&       ranges,
													bool                             is_looped)
{
	mIsLooped = is_looped;
	mAnimationTextures = textures;
	
	if (mAnimationTextures.size() > 0)
	{
		mCurFrame = 0;
		mIsPlaying = true;
		SetTexture(mAnimationTextures[0]);

		mAnimationRanges = ranges.size() > 0 ? ranges : std::vector<Uint32>({ 0, mAnimationTextures.size() });
	}
}

int AnimationSpriteComponent::GetAnimationSize(Uint8 id) const
{
	if (id < GetAnimationCount())
	{
		return mAnimationRanges[id + 1] - mAnimationRanges[id];
	}
}

void AnimationSpriteComponent::SetAnimation(Uint8 id)
{
	if (id < GetAnimationCount() && !mIsPlaying)
	{
		mIsPlaying = true;
		mCurAnimationId = id;
		mCurFrame = mAnimationRanges[mCurAnimationId];
	}
}
