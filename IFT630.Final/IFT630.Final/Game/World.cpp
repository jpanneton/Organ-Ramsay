#include "World.h"
#include "Engine/Utilities/Math.h"
#include "Engine/Utilities/Utilities.h"
#include "Game/ResourceIdentifiers.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <algorithm>

World::World(State::Context context)
	: m_context{ context }
	, m_worldView{ context.window->getDefaultView() }
	, m_worldBounds{ 0.f, 0.f, m_worldView.getSize().x, m_worldView.getSize().y }
    , m_humanBody{ context }
{
	buildScene();
}

void World::update(sf::Time dt)
{
    const float fps = 60.f;
    m_humanBody.update(fps);
}

void World::draw() const
{
    m_context.window->setView(m_worldView);
    m_humanBody.draw();
    m_context.window->setView(m_worldView);
}

void World::moveView(const sf::Vector2f& delta)
{
    m_worldView.move(m_worldView.getSize().x / m_context.window->getSize().x * delta);
}

void World::zoomView(const sf::Vector2i& position, float zoomAmount)
{
    Util::zoomViewAt(*m_context.window, m_worldView, position, zoomAmount);
}

void World::buildScene()
{
    m_humanBody.init();
}