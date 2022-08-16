#include "BGSpriteComponent.h"
#include "Actor.h"
#include "Math.h"

BGSpriteComponent::BGSpriteComponent(Actor* owner, int drawOrder) :
	SpriteComponent(owner, drawOrder),
	mScrollSpeed(0.f)
{
}

void BGSpriteComponent::Update(float deltaTime)
{
	SpriteComponent::Update(deltaTime);

	for (auto& bg_texture : mBGTextures)
	{
		bg_texture.mOffset.x += mScrollSpeed * deltaTime;
		if (bg_texture.mOffset.x < -mScreenSize.x)
		{
			bg_texture.mOffset.x = (mBGTextures.size() - 1) * mScreenSize.x - 1;
		}
	}
}

void BGSpriteComponent::Draw(SDL_Renderer* renderer)
{
	for (auto& bg_texture : mBGTextures)
	{
		SDL_Rect rect;

		rect.w = static_cast<int>(mScreenSize.x);
		rect.h = static_cast<int>(mScreenSize.y);

		rect.x = static_cast<int>(mOwner->GetPosition().x - rect.w / 2 + bg_texture.mOffset.x);
		rect.y = static_cast<int>(mOwner->GetPosition().y - rect.h / 2 + bg_texture.mOffset.y);

		SDL_RenderCopy(renderer, bg_texture.mTexture, nullptr, &rect);
	}
}

void BGSpriteComponent::SetBGTextures(const std::vector<SDL_Texture*>& textures)
{
	int count = 0;
	for (auto& texture : textures)
	{
		BGTexture temp;
		temp.mTexture = texture;

		temp.mOffset.x = count * mScreenSize.x;
		temp.mOffset.y = 0;

		mBGTextures.emplace_back(temp);
		++count;
	}
}
