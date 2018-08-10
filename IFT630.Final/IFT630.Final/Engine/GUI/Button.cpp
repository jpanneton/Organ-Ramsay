#include "Button.h"
#include "Engine/ResourceHolder.h"
#include "Engine/Utilities/Utilities.h"
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Window/Event.hpp>

using namespace GUI;

Button::Button(const FontHolder& fonts, const TextureHolder& textures)
	: m_callback{}
	, m_normalTexture{ textures.get(TexturesID::ButtonNormal) }
	, m_selectedTexture{ textures.get(TexturesID::ButtonSelected) }
	, m_pressedTexture{ textures.get(TexturesID::ButtonPressed) }
	, m_sprite{}
	, m_text{ "", fonts.get(FontsID::Main), 16 }
	, m_isToggled{ false }
{
	m_sprite.setTexture(m_normalTexture);
	sf::FloatRect bounds = m_sprite.getLocalBounds();
	m_text.setPosition(bounds.width / 2.f, bounds.height / 2.f);
}

void Button::setCallback(Callback callback)
{
	m_callback = std::move(callback);
}

void Button::setText(const std::string& text)
{
	m_text.setString(text);
	Util::centerOrigin(m_text);
}

void Button::toggle(bool flag)
{
	m_isToggled = flag;
}

bool Button::isSelectable() const
{
	return true;
}

void Button::select()
{
	Component::select();
	m_sprite.setTexture(m_selectedTexture);
}

void Button::deselect()
{
	Component::deselect();
	m_sprite.setTexture(m_normalTexture);
}

void Button::activate()
{
	Component::activate();

	if (m_isToggled)
	{
		m_sprite.setTexture(m_pressedTexture);
	}

	if (m_callback)
	{
		m_callback();
	}

	// If we are not a toggle then deactivate the button since we are just momentarily activated.
	if (!m_isToggled)
	{
		deactivate();
	}
}

void Button::deactivate()
{
	Component::deactivate();

	if (m_isToggled)
	{
		// Reset texture to right one depending on if we are selected or not.
		if (isSelected())
		{
			m_sprite.setTexture(m_selectedTexture);
		}
		else
		{
			m_sprite.setTexture(m_normalTexture);
		}
	}
}

void Button::handleEvent(const sf::Event&)
{
}

bool Button::handleMouseEvent(const sf::Event& event, bool mouseMovedEvent)
{
	const sf::Vector2i mousePosition = mouseMovedEvent ?
		sf::Vector2i{ event.mouseMove.x, event.mouseMove.y } :
		sf::Vector2i{ event.mouseButton.x, event.mouseButton.y };
	const sf::Vector2i buttonPosition{ getPosition() };
	const sf::IntRect buttonBounds{ buttonPosition.x, buttonPosition.y,
		m_sprite.getTextureRect().width, m_sprite.getTextureRect().height };
	return buttonBounds.contains(mousePosition);
}

void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(m_sprite, states);
	target.draw(m_text, states);
}