#include "PauseState.h"
#include "Engine/ResourceHolder.h"
#include "Engine/Utilities.h"
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

PauseState::PauseState(StateStack& stack, Context context)
	: State{ stack, context }
	, m_backgroundSprite{}
	, m_pausedText{}
	, m_instructionText{}
{
	sf::Font& font = context.fonts->get(FontsID::Main);
	sf::Vector2f viewSize = context.window->getView().getSize();

	m_pausedText.setFont(font);
	m_pausedText.setString("Game paused");
	m_pausedText.setCharacterSize(70);
	Util::centerOrigin(m_pausedText);
	m_pausedText.setPosition(0.5f * viewSize.x, 0.4f * viewSize.y);

	m_instructionText.setFont(font);
	m_instructionText.setString("(Press Backspace to quit)");
	Util::centerOrigin(m_instructionText);
	m_instructionText.setPosition(0.5f * viewSize.x, 0.6f * viewSize.y);
}

void PauseState::draw()
{
	sf::RenderWindow& window = *getContext().window;
	window.setView(window.getDefaultView());

	sf::RectangleShape backgroundShape;
	backgroundShape.setFillColor(sf::Color(0, 0, 0, 150));
	backgroundShape.setSize(window.getView().getSize());

	window.draw(backgroundShape);
	window.draw(m_pausedText);
	window.draw(m_instructionText);
}

bool PauseState::update(sf::Time)
{
	return false; // Prevent lower states from being updated
}

bool PauseState::handleEvent(const sf::Event& event)
{
	if (event.type != sf::Event::KeyPressed)
	{
		return false;
	}

	if (event.key.code == sf::Keyboard::Escape)
	{
		// Return to game (pop this state)
		requestStackPop();
	}

	if (event.key.code == sf::Keyboard::BackSpace)
	{
		// Return to main menu (init all states)
		requestStackClear();
	}

	return false; // Prevent lower states events from being handled
}