#pragma once

// Name: Button.h
// Author: Jérémi Panneton
// Description: GUI button class

#include "Component.h"
#include "Game/ResourceIdentifiers.h"
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include <functional>
#include <memory>

namespace GUI
{
	/// @brief GUI button
	/// @author Jeremi Panneton
	/// @ingroup engine
	class Button : public Component
	{
	public:
		using Ptr = std::shared_ptr<Button>;
		using Callback = std::function<void()>;

		//========================================

		/// @brief Construct a button with different states textures
		/// @param[in] fonts Available fonts
		/// @param[in] textures Available textures
		Button(const FontHolder& fonts, const TextureHolder& textures);

		//----------------------------------------

		/// @brief Set the code to execute when the button is triggered
		/// @param[in] callback Code to execute (function)
		void setCallback(Callback callback);

		/// @brief Set inner button text
		/// @param[in] text Inner button text
		void setText(const std::string& text);

		/// @brief Set if the button should remain in pressed state or not
		/// @param[in] flag If it should remain in pressed state or not
		void toggle(bool flag);

		//----------------------------------------

		/// @see Component::isSelectable
		bool isSelectable() const override;

		/// @see Component::select
		void select() override;

		/// @see Component::deselect
		void deselect() override;

		//----------------------------------------

		/// @see Component::activate
		void activate() override;

		/// @see Component::deactivate
		void deactivate() override;

		//----------------------------------------

		/// @see Component::handleEvent
		void handleEvent(const sf::Event& event) override;

		/// @see Component::handleMouseEvent
		bool handleMouseEvent(const sf::Event& event, bool mouseMovedEvent) override;

	private:
		/// @see Container::draw
		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

		//========================================

		/// @brief Code to execute when the button is triggered
		Callback m_callback;
		/// @brief Idle state texture
		const sf::Texture& m_normalTexture;
		/// @brief Selected state texture
		const sf::Texture& m_selectedTexture;
		/// @brief Pressed state texture
		const sf::Texture& m_pressedTexture;
		/// @brief Current button sprite
		sf::Sprite m_sprite;
		/// @brief Button text
		sf::Text m_text;
		/// @brief If the button should remain in pressed state or not
		bool m_isToggled;
	};

}