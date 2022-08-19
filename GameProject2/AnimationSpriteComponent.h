#pragma once
#include "SpriteComponent.h"
#include <vector>

class AnimationSpriteComponent : public SpriteComponent
{
public:
	AnimationSpriteComponent(class Actor* owner, int drawOrder = 100);

	void Update(float deltaTime) override;
	void SetAnimationTextures(const std::vector<SDL_Texture*>& textures,
		                      const std::vector<Uint32>&       ranges = {},
		                      bool                             is_looping = false);

	float GetAnimationFPS() const { return mAnimationFPS; }
	int GetAnimationSize(Uint8 id) const;
	int GetAnimationCount() const { return mAnimationRanges.size() - 1; }
	bool GetLoopState() const { return mIsLooped; }
	bool GetPlayState() const { return mIsPlaying; }

	void SetAnimationFPS(float fps) { mAnimationFPS = fps; }
	void SetAnimation(Uint8 id);
	void SetLoopState(bool is_looped) { mIsLooped = is_looped; }
	void SetPlayState(bool is_playing) { mIsPlaying = is_playing; }

private:
	std::vector<SDL_Texture*> mAnimationTextures;
	float mCurFrame;
	float mAnimationFPS;

	Uint8 mCurAnimationId;
	std::vector<Uint32> mAnimationRanges;

	bool mIsLooped;
	bool mIsPlaying;
};

