#include "AnimationSpriteComponent.h"
//#include "Actor.h"

AnimationSpriteComponent::AnimationSpriteComponent(Actor* owner, int drawOrder) : 
	SpriteComponent(owner, drawOrder),
	mCurFrame(0.f),
	mAnimationFPS(24.f),
	mCurAnimationId(0)
{
}

void AnimationSpriteComponent::Update(float deltaTime)
{
	SpriteComponent::Update(deltaTime);

	if (mAnimationTextures.size() > 0)
	{
		mCurFrame += mAnimationFPS * deltaTime;

		//while (mCurFrame >= mAnimationTextures.size())
		while (mCurFrame >= mAnimationRanges[mCurAnimationId + 1]/*GetAnimationSize(mCurAnimationId)*/)
		{
			
			//mCurFrame -= mAnimationTextures.size();
			mCurFrame -= GetAnimationSize(mCurAnimationId);
		}

		SetTexture(mAnimationTextures[static_cast<int>(mCurFrame)]);
	}
}

void AnimationSpriteComponent::SetAnimationTextures(const std::vector<SDL_Texture*>& textures,
													const std::vector<Uint32>&       ranges)
{
	mAnimationTextures = textures;
	
	if (mAnimationTextures.size() > 0)
	{
		mCurFrame = 0;
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
	if (id < GetAnimationCount())
	{
		mCurAnimationId = id;
		mCurFrame = mAnimationRanges[mCurAnimationId];
	}
}
