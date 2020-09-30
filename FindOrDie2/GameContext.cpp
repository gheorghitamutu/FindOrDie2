#include "GameContext.hpp"

ge::game_context::game_context() :
    machine_(std::make_shared<state_machine>(state_machine())),
    asset_manager_(std::make_shared<asset_manager>(asset_manager())),
    input_manager_(std::make_shared<input_manager>(input_manager()))
{
    render_window_.reset(new sf::RenderWindow(
        sf::VideoMode(sf::VideoMode::getFullscreenModes()[0]),
        sf::String(GAME_TITLE),
        sf::Style::Close | sf::Style::Titlebar));

    camera_.reset(new camera(render_window_));
}
