#pragma once
#include <SFML/Graphics.hpp>
#include <map>

class ResourceManager
{
private:
	ResourceManager() noexcept;
	void LoadTexture(std::string path, std::string name);

public:
	static ResourceManager* GetInstance()
	{
		static ResourceManager instance;
		return &instance;
	}
	~ResourceManager();
	sf::Texture* RequestTexture(std::string name);
	void CleanUp();

private:
	std::map<std::string, sf::Texture*> m_Textures;
};

