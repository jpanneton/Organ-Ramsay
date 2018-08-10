#include "Container.h"
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Window/Event.hpp>

using namespace GUI;

Container::Container()
	: m_children{}
	, m_selectedChild{ -1 }
{
}

void Container::pack(Component::Ptr component)
{
	m_children.push_back(component);

	if (!hasSelection() && component->isSelectable())
	{
		select(m_children.size() - 1);
	}
}

bool Container::isSelectable() const
{
	return false;
}

void Container::handleEvent(const sf::Event& event)
{
	// If we have selected a child then give it events
	if (hasSelection() && m_children[m_selectedChild]->isActivated())
	{
		m_children[m_selectedChild]->handleEvent(event);
	}
	else if (event.type == sf::Event::MouseMoved)
	{
		handleMouseEvent(event, true);
	}
	else if (event.type == sf::Event::MouseButtonReleased)
	{
		handleMouseEvent(event, false);
	}
	else if (event.type == sf::Event::KeyReleased)
	{
		if (event.key.code == sf::Keyboard::W || event.key.code == sf::Keyboard::Up)
		{
			selectPrevious();
		}
		else if (event.key.code == sf::Keyboard::S || event.key.code == sf::Keyboard::Down)
		{
			selectNext();
		}
		else if (event.key.code == sf::Keyboard::Return || event.key.code == sf::Keyboard::Space)
		{
			if (hasSelection())
			{
				m_children[m_selectedChild]->activate();
			}
		}
	}
}

bool Container::handleMouseEvent(const sf::Event& event, bool mouseMovedEvent)
{
	// Mouse movement
	if (mouseMovedEvent)
	{
		size_t i = 0;
		for (; i < m_children.size(); ++i)
		{
			if (m_children[i]->handleMouseEvent(event, mouseMovedEvent))
			{
				select(i);
				break;
			}
		}
		return i != m_children.size();
	}

	// Mouse buttons
	if (hasSelection() && m_children[m_selectedChild]->handleMouseEvent(event, mouseMovedEvent))
	{
		m_children[m_selectedChild]->activate();
		return true;
	}

	return false;
}

void Container::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();

	for (const Component::Ptr& child : m_children)
	{
		target.draw(*child, states);
	}
}

bool Container::hasSelection() const
{
	return m_selectedChild >= 0;
}

void Container::select(size_t index)
{
	if (m_children[index]->isSelectable())
	{
		if (hasSelection())
		{
			m_children[m_selectedChild]->deselect();
		}

		m_children[index]->select();
		m_selectedChild = static_cast<int>(index);
	}
}

void Container::selectNext()
{
	if (!hasSelection())
		return;

	int next = m_selectedChild;

	do // Search next component that is selectable, wrap around if necessary
	{
		next = (next + 1) % m_children.size();
	} while (!m_children[next]->isSelectable());

	// Select that component
	select(next);
}

void Container::selectPrevious()
{
	if (!hasSelection())
		return;

	int previous = m_selectedChild;
	const int childrenCount = static_cast<int>(m_children.size());

	do // Search previous component that is selectable, wrap around if necessary
	{
		previous = (previous + childrenCount - 1) % childrenCount;
	} while (!m_children[previous]->isSelectable());

	// Select that component
	select(previous);
}