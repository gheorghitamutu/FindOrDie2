#include "AssetManager.hpp"

namespace ge
{
	asset_manager::asset_manager()
	{
		load_texture("Ghost",		"Resources/Sprites/ghost.png");
		load_texture("Player_Man",	"Resources/Sprites/Player_Man/man.png");
		load_texture("Full_Block",	"Resources/Sprites/Tiles/Terrain/full_block.png");
	}

	void asset_manager::load_texture(const std::string& name, const std::string& file_name)
	{
		auto texture = std::make_shared<sf::Texture>(sf::Texture());

		const auto texture_loaded = texture->loadFromFile(file_name);

		if (texture_loaded)
		{
			textures_[name] = texture;
		}
	}

	std::shared_ptr<sf::Texture> asset_manager::get_texture(const std::string& name)
	{
		const auto texture = textures_[name];

		return texture != nullptr ? texture : nullptr;
	}

	void asset_manager::load_font(const std::string& name, const std::string& file_name)
	{
		auto font = std::make_shared<sf::Font>(sf::Font());

		if (font->loadFromFile(file_name))
		{
			fonts_[name] = font;
		}
	}

	std::shared_ptr<sf::Font> asset_manager::get_font(const std::string& name)
	{
		const auto font = fonts_[name];

		return font != nullptr ? font : nullptr;
	}
}