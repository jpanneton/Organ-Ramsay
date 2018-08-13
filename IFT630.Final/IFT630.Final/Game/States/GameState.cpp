#include "GameState.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp> // Needed

GameState::GameState(StateStack& stack, Context context)
	: State{ stack, context }
	, m_world{ context }
{
}

void GameState::draw()
{
	m_world.draw();
}

bool GameState::update(sf::Time dt)
{
	m_world.update(dt);
	return true;
}

bool GameState::handleEvent(const sf::Event& event)
{
	m_world.handleEvent(event);

	if (event.type == sf::Event::MouseMoved)
	{
        static sf::Vector2f lastMousePosition{ sf::Mouse::getPosition(*getContext().window) };
        const sf::Vector2f mousePosition{ sf::Mouse::getPosition(*getContext().window) };
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            m_world.moveCamera(lastMousePosition - mousePosition);
        lastMousePosition = mousePosition;
	}
    else if (event.type == sf::Event::MouseWheelScrolled)
    {
        float zoomAmount = 1.1f;
        if (event.mouseWheelScroll.delta > 0.f)
            zoomAmount = 1.f / zoomAmount;
        m_world.zoomCamera({ event.mouseWheelScroll.x, event.mouseWheelScroll.y }, zoomAmount);
    }

	// Escape pressed, trigger the pause screen
	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
	{
		requestStackPush(StatesID::Pause);
	}

	return true;
}