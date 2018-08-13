#include "World.h"
#include "Engine/Utilities.h"
#include "Game/ResourceIdentifiers.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <algorithm>
#include <iostream>

World::World(State::Context context)
	: m_context{ context }
	, m_worldView{ context.window->getDefaultView() }
	, m_worldBounds{ 0.f, 0.f, m_worldView.getSize().x, m_worldView.getSize().y }
    , m_humanBody{ context }
{
	buildScene();
	moveCamera(sf::Vector2f(-150.f, 0.f));
}

void World::update(sf::Time dt)
{
	m_humanBody.update(60.f);
}

void World::handleEvent(const sf::Event& event)
{
	if (event.type == sf::Event::TextEntered)
	{
		system("cls");

		if (event.text.unicode == 8) // Backspace
		{
			m_keyboardInput = m_keyboardInput.substr(0, m_keyboardInput.length() - 1);
		}
		else if(event.text.unicode == 10 || event.text.unicode == 13) // Enter
		{
			if (!m_humanBody.setInfo(m_keyboardInput))
			{
				std::cout << "Format attendu: [bpm | cpm | oxygen | energy | excrement] = valeur" << std::endl;
			}

			m_keyboardInput.clear();
		}
		else
		{
			m_keyboardInput += static_cast<char>(event.text.unicode);
		}

		std::cout << m_keyboardInput;
	}
}

void World::draw() const
{
    m_context.window->setView(m_worldView);
    m_humanBody.draw();
    m_context.window->setView(m_worldView);
}

void World::moveCamera(const sf::Vector2f& delta)
{
    m_worldView.move(m_worldView.getSize().x / m_context.window->getSize().x * delta);
}

void World::zoomCamera(const sf::Vector2i& position, float zoomAmount)
{
    Util::zoomViewAt(*m_context.window, m_worldView, position, zoomAmount);
}

void World::buildScene()
{
    m_humanBody.init();
}