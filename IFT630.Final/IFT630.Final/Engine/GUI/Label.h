#pragma once

// Name: Label.h
// Author: Jérémi Panneton
// Description: GUI label class

#include "Engine/GUI/Component.h"
#include "Engine/ResourceHolder.h"
#include "Game/ResourceIdentifiers.h"
#include <SFML/Graphics/Text.hpp>

namespace GUI
{
	/// @brief GUI label (simple text)
	/// @author Jeremi Panneton
	/// @ingroup engine
	class Label : public Component
	{
	public:
		using Ptr = std::shared_ptr<Label>;

		//========================================

		/// @brief Construct a label with text
		/// @param[in] text Actual text
		/// @param[in] fonts Available fonts
		Label(const std::string& text, const FontHolder& fonts);

		//----------------------------------------
		
		/// @see Component::isSelectable
		bool isSelectable() const override;

		/// @brief Set label text
		/// @param[in] text Label text
		void setText(const std::string& text);

		//----------------------------------------

		/// @see Component::handleEvent
		void handleEvent(const sf::Event& event) override;

		/// @see Component::handleMouseEvent
		bool handleMouseEvent(const sf::Event& event, bool mouseMovedEvent) override;

	private:
		/// @see Container::draw
		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

		//========================================

		/// @brief Current label text
		sf::Text m_text;
	};

}