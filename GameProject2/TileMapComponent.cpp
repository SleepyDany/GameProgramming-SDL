#include "TileMapComponent.h"

TileMapComponent::TileMapComponent(Actor* owner, int drawOrder) :
	SpriteComponent(owner, drawOrder),
	mTileSet(nullptr),
	mPositions(nullptr),
	mSize(Vector2(0, 0)),
	mColumnCount(0),
	mRowCount(0)
{
}

TileMapComponent::~TileMapComponent()
{
	for (Uint32 i = 0; i < mRowCount; ++i)
		delete[] mPositions[i];
	delete[] mPositions;
	mPositions = nullptr;

	delete mTileSet;
	mTileSet = nullptr;

	SpriteComponent::~SpriteComponent();
}

void TileMapComponent::Load(const std::string& map_file, const Vector2& size)
{
	if (std::filesystem::path(map_file).extension() == ".tsx")
	{
		mTileSet = new TileSet();
		mSize = size;

		std::ifstream file(map_file);
		std::string position_file;
		
		if (file.is_open())
		{
			std::vector<char> buffer((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
			buffer.push_back('\0');

			rapidxml::xml_document<> doc;
			rapidxml::xml_node<>* root_node;

			doc.parse<0>(&buffer[0]);
			root_node = doc.first_node("tileset");

			mTileSet->mTileCount = atoi(root_node->first_attribute("tilecount")->value());
			mTileSet->mTileWidth = atoi(root_node->first_attribute("tilewidth")->value());
			mTileSet->mTileHeight = atoi(root_node->first_attribute("tileheight")->value());
			mTileSet->mColumnCount = atoi(root_node->first_attribute("columns")->value());
			mTileSet->mRowCount = mTileSet->mTileCount / mTileSet->mColumnCount;

			rapidxml::xml_node<>* node = root_node->first_node();

			while (node != 0)
			{
				if (strcmp(node->name(), "properties") == 0)
				{
					if (strcmp(node->first_node("property")->first_attribute("name")->value(), "position") == 0)
					{
						position_file = node->first_node("property")->first_attribute("value")->value();
					}
				}
				else if (strcmp(node->name(), "image") == 0)
				{
					mTileSet->mSource = node->first_attribute("source")->value();
					SetTexture(mOwner->GetGame()->GetTexture(mTileSet->mSource));
				}

				node = node->next_sibling();
			}

			doc.clear();
		}
		file.close();
		
		file.open(position_file);
		if (file.is_open())
		{
			mColumnCount = static_cast<Uint32>(mSize.x / mTileSet->mTileWidth);
			mRowCount = static_cast<Uint32>(mSize.y / mTileSet->mTileHeight);
			std::string line;

			mPositions = new int* [mRowCount] {};
			for (Uint32 i = 0; i < mRowCount; ++i)
			{
				mPositions[i] = new int[mColumnCount]{};

				std::getline(file, line);
				int end = 0, begin = 0;
				
				for (Uint32 j = 0; j < mColumnCount; ++j)
				{
					end = line.find(',', begin);
					mPositions[i][j] = std::stoi(line.substr(begin, end - begin));
					begin = end + 1;
				}
			}
		}

		file.close();
	}
}

void TileMapComponent::Draw(SDL_Renderer* renderer)
{
	SDL_Rect src_rect, dst_rect;

	dst_rect.w = static_cast<int>(mTileSet->mTileWidth * mOwner->GetScale());
	dst_rect.h = static_cast<int>(mTileSet->mTileWidth * mOwner->GetScale());

	for (Uint32 i = 0; i < mRowCount; ++i)
	{
		for (Uint32 j = 0; j < mColumnCount; ++j)
		{
			int tile_id = mPositions[i][j];

			if (tile_id == -1)
				continue;
			else
			{
				dst_rect.x = static_cast<int>(mOwner->GetPosition().x - 512.f + j * mTileSet->mTileWidth);
				dst_rect.y = static_cast<int>(mOwner->GetPosition().y - 384.f + i * mTileSet->mTileHeight);

				src_rect.w = static_cast<int>(mTileSet->mTileWidth * mOwner->GetScale());
				src_rect.h = static_cast<int>(mTileSet->mTileHeight * mOwner->GetScale());

				src_rect.x = static_cast<int>((tile_id % mTileSet->mColumnCount) * mTileSet->mTileWidth);
				src_rect.y = static_cast<int>((tile_id / mTileSet->mColumnCount) * mTileSet->mTileHeight);

				SDL_RenderCopyEx(renderer, mTexture, &src_rect, &dst_rect, -Math::ToDegrees(mOwner->GetRotation()), nullptr, SDL_FLIP_NONE);
			}
		}
	}
}
