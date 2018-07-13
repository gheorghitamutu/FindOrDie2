#include "stdafx.h"
#include "ResourceManager.h"


ResourceManager::ResourceManager()
{
	LoadTexture("Resources/Sprites/ghost.png", "Ghost");
}

void ResourceManager::LoadTexture(std::string path, std::string name)
{
	m_Textures[name] = new sf::Texture;
	m_Textures[name]->loadFromFile(path);
}


ResourceManager::~ResourceManager()
{
}

sf::Texture * ResourceManager::RequestTexture(std::string name)
{
	if (m_Textures[name]) return m_Textures[name];

	return nullptr;
}

void ResourceManager::CleanUp()
{
	for (auto item : m_Textures)
	{
		delete item.second;
		item.second = nullptr;
	}
}
