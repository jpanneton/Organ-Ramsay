#pragma once

// Name: Container.h
// Author: Jérémi Panneton
// Description: GUI container class

#include "Component.h"
#include <memory>
#include <vector>

namespace GUI
{
	/// @brief GUI container (hierarchy component)
	/// @author Jeremi Panneton
	/// @ingroup engine
	class Container : public Component
	{
	public:
		using Ptr = std::shared_ptr<Container>;

		//========================================

		/// @brief Default constructor
		Container();

		/// @brief Add another component as a child of the current container
		/// @param[in] component Component to add
		void pack(Component::Ptr component);

		//----------------------------------------

		/// @see Component::isSelectable
		bool isSelectable() const override;

		/// @see Component::handleEvent
		void handleEvent(const sf::Event& event) override;

	protected:
		/// @see Component::handleMouseEvent
		bool handleMouseEvent(const sf::Event& event, bool mouseMovedEvent) override;

	private:
		/// @brief Draw GUI component (in this case a container) to render target
		/// @param[in] target Render target to draw to
		/// @param[in] states States used for drawing to render target (transforms, shader, etc.)
		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

		//----------------------------------------

		/// @brief Check if one of the current container children is selected or not
		/// @return If one of the children is selected or not
		bool hasSelection() const;

		/// @brief Select a child of the current container from an index
		/// @param[in] index Index of the child in the container (sorted in order of insertion)
		void select(size_t index);

		/// @brief Select next child of the container from the currently selected one
		void selectNext();

		/// @brief Select previous child of the container from the currently selected one
		void selectPrevious();

		//========================================

		/// @brief Children GUI components
		std::vector<Component::Ptr> m_children;
		/// @brief Selected child index (none if negative)
		int m_selectedChild;
	};
}