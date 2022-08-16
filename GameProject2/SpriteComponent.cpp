#include "SpriteComponent.h"
#include "Actor.h"
#include "Game.h"
#include "Math.h"
#include <iostream>

SpriteComponent::SpriteComponent(Actor* owner, int drawOrder) :
	Component(owner),
	mDrawOrder(drawOrder),
	mTexture(nullptr),
	mTextureHeight(0),
	mTextureWidth(0)
{
	mOwner->GetGame()->AddSprite(this);
}

SpriteComponent::~SpriteComponent()
{
	mOwner->GetGame()->RemoveSprite(this);
}

void SpriteComponent::Draw(SDL_Renderer* renderer)
{
	if (mTexture)
	{
		SDL_Rect rect;
		rect.w = static_cast<int>(mTextureWidth * mOwner->GetScale());
		rect.h = static_cast<int>(mTextureHeight * mOwner->GetScale());

		rect.x = static_cast<int>(mOwner->GetPosition().x - rect.w / 2);
		rect.y = static_cast<int>(mOwner->GetPosition().y - rect.h / 2);

		SDL_RenderCopyEx(renderer, mTexture, nullptr, &rect, -Math::ToDegrees(mOwner->GetRotation()), nullptr, SDL_FLIP_NONE);
	}
}

void SpriteComponent::SetTexture(SDL_Texture* texture)
{
	mTexture = texture;
	SDL_QueryTexture(texture, nullptr, nullptr, &mTextureWidth, &mTextureHeight);
}
