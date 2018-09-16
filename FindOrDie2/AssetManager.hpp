#pragma once

#include <map>

#include <SFML/Graphics.hpp>

namespace ge
{
	class asset_manager
	{
	public:
		asset_manager();

		asset_manager(const asset_manager& other) = default;
		asset_manager(asset_manager&& other) noexcept = default;
		asset_manager& operator=(const asset_manager& other) = default;
		asset_manager& operator=(asset_manager&& other) noexcept = default;

		~asset_manager() = default;

		void load_texture(const std::string& name, const std::string& file_name);
		std::shared_ptr<sf::Texture> get_texture(const std::string& name);
		
		void load_font(const std::string& name, const std::string& file_name);
		std::shared_ptr<sf::Font> get_font(const std::string& name);

	private:
		std::map<std::string, std::shared_ptr<sf::Texture>> textures_;
		std::map<std::string, std::shared_ptr<sf::Font>> fonts_;
	};
}
