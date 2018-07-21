#include "AssetManager.h"

namespace GameEngine
{
	AssetManager::AssetManager()
	{
		LoadTexture("Resources/Sprites/ghost.png", "Ghost");
		LoadTexture("Resources/Sprites/Player_Man/man.png", "Player_Man");
		LoadTexture("Resources/Sprites/TerrainTiles/full_block.png", "Full_Block");
	}

	AssetManager::~AssetManager()
	{
	}

	void AssetManager::LoadTexture(std::string name, std::string fileName)
	{
		auto texture = new sf::Texture;

		bool textureLoaded = texture->loadFromFile(fileName);
		if (textureLoaded)
		{
			m_Textures[name] = texture;
		}
		else
		{
			delete texture;
		}
	}

	sf::Texture* AssetManager::GetTexture(std::string name)
	{
		auto texture = m_Textures[name];

		return texture != nullptr ? texture : nullptr;
	}

	void AssetManager::LoadFont(std::string name, std::string fileName)
	{
		auto font = new sf::Font;

		if (font->loadFromFile(fileName))
		{
			m_Fonts[name] = font;
		}
		else
		{
			delete font;
		}
	}

	sf::Font* AssetManager::GetFont(std::string name)
	{
		auto font = m_Fonts[name];

		return font != nullptr ? font : nullptr;
	}

	void AssetManager::CleanUp()
	{
		for (auto item : m_Textures)
		{
			delete item.second;
			item.second = nullptr;
		}

		for (auto item : m_Fonts)
		{
			delete item.second;
			item.second = nullptr;
		}
	}
}