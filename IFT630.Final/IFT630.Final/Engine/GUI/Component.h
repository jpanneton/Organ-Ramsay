#pragma once

// Name: Component.h
// Author: Jérémi Panneton
// Description: Base GUI component class

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/System/NonCopyable.hpp>
#include <memory>

// Forward declaration
namespace sf
{
	class Event;
}

namespace GUI
{
	/// @brief GUI base component
	/// @author Jeremi Panneton
	/// @ingroup engine
	class Component : public sf::Drawable, public sf::Transformable, sf::NonCopyable
	{
	public:
		using Ptr = std::shared_ptr<Component>;

		//========================================

		/// @brief Default constructor
		Component();

		/// @brief Virtual destructor (for safe derived component destruction)
		virtual ~Component();

		//----------------------------------------

		/// @brief If the GUI component is selectable or not (reactive to input events)
		/// @return If the component is selectable or not
		virtual bool isSelectable() const = 0;

		/// @brief If the GUI component is selected or not
		/// @return If the component is selected or not
		bool isSelected() const;

		/// @brief Select the GUI component
		virtual void select();

		/// @brief Deselect the GUI component
		virtual void deselect();

		//----------------------------------------

		/// @brief If the GUI component is activated or not
		/// @return If the component is activated or not
		virtual bool isActivated() const;

		/// @brief Activate the GUI component (e.g. trigger a button)
		virtual void activate();

		/// @brief Deactivate the GUI component
		virtual void deactivate();

		//----------------------------------------

		/// @brief Handle GUI component input event
		/// @param[in] event Input event
		virtual void handleEvent(const sf::Event& event) = 0;

		/// @brief Handle GUI component mouse event
		/// @param[in] event Mouse event
		/// @param[in] mouseMovedEvent If the mouse event is a MouseMovedEvent or not
		/// @return If the mouse event was within component's bounds or not
		virtual bool handleMouseEvent(const sf::Event& event, bool mouseMovedEvent) = 0;

	private:
		/// @brief If the component is selected or not
		bool m_isSelected;
		/// @brief If the component is activated or not
		bool m_isActivated;
	};
}