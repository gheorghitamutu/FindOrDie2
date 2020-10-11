#include "GameContext.hpp"

ge::game_context::game_context()
{
    machine_.reset(new state_machine());
    asset_manager_.reset(new asset_manager());
    input_manager_.reset(new input_manager());

    render_window_.reset(new sf::RenderWindow(
        sf::VideoMode(sf::VideoMode::getFullscreenModes()[0]),
        sf::String(GAME_TITLE),
        sf::Style::Close | sf::Style::Titlebar));

    camera_.reset(new camera(render_window_));   
}
