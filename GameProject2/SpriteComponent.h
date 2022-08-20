#pragma once
#include "Component.h"
#include "Game.h"
#include "Math.h"
#include "SDL.h"

class SpriteComponent : public Component
{
public:
	SpriteComponent(Actor* owner, int drawOrder = 100);
	~SpriteComponent() override;

	virtual void Draw(SDL_Renderer* renderer);
	virtual void SetTexture(SDL_Texture* texture);

	int GetDrawOrder() const { return mDrawOrder; }
	int GetTextureHeight() const { return mTextureHeight; }
	int GetTextureWigth() const { return mTextureWidth;  }

protected:
	SDL_Texture* mTexture;

	int mDrawOrder;
	int mTextureHeight;
	int mTextureWidth;
};

