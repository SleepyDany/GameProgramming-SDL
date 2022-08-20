#pragma once
#include "SpriteComponent.h"
#include <string>
#include <vector>
#include <filesystem>
#include <iostream>
#include <fstream>
#include <algorithm>
#include "../rapidxml-1.13/rapidxml.hpp"

class TileSet
{
public:
	TileSet() : mRowCount(0),
				mColumnCount(0),
				mTileCount(0),
				mTileWidth(0),
				mTileHeight(0)
	{
	};

	~TileSet() {};

	Uint32 mRowCount;
	Uint32 mColumnCount;
	Uint32 mTileCount;

	Uint32 mTileWidth;
	Uint32 mTileHeight;

	std::string mSource;
};

class TileMapComponent : public SpriteComponent
{
public:
	TileMapComponent(Actor* owner, int drawOrder = 100);
	~TileMapComponent();

	void Load(const std::string& map_file, const Vector2& size = Vector2(1024, 768));
	void Draw(SDL_Renderer* renderer) override;

	void SetSize(Vector2& size) { mSize = size; }

private:

	TileSet* mTileSet;

	Uint32** mPositions;

	Uint32 mRowCount;
	Uint32 mColumnCount;

	Vector2 mSize;
};

