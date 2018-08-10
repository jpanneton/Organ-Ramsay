#pragma once

// Name: State.h
// Author: Jérémi Panneton
// Description: Base state class

#include "Game/ResourceIdentifiers.h"
#include "Game/States/StateIdentifiers.h"
#include <SFML/System/Time.hpp>
#include <SFML/Window/Event.hpp>
#include <memory>

namespace sf
{
	class RenderWindow;
}

class PlayerController;
class StateStack;

/// @brief Game state
/// @author Jeremi Panneton
/// @ingroup engine
class State
{
public:
	using Ptr = std::unique_ptr<State>;
	
	/// @brief Pointers to main shared game resources
	/// @author Jeremi Panneton
	struct Context
	{
		/// @brief Create access to main shared game resources
		/// @param[in] window Main render window
		/// @param[in] textures Main texture holder
		/// @param[in] fonts Main font holder
		Context(sf::RenderWindow& window, TextureHolder& textures, FontHolder& fonts);

		/// @brief Pointer to main render window
		sf::RenderWindow* window;
		/// @brief Pointer to main texture resources
		TextureHolder* textures;
		/// @brief Pointer to main font resources
		FontHolder* fonts;
	};
	
	//========================================

	/// @brief Construct a default state
	/// @param[in] stack Owning stack
	/// @param[in] context Current game context
	State(StateStack& stack, Context context);

	/// @brief Virtual destructor (for safe derived state destruction)
	virtual ~State() = default;

	/// @brief Update all state elements
	/// @param[in] dt Elapsed time since last update
	/// @return If the next state should be updated or not
	virtual bool update(sf::Time dt) = 0;

	/// @brief Draw all state elements that need to be drawn
	virtual void draw() = 0;

	/// @brief Handle state specific event
	/// @param[in] event Input event
	/// @return If the event should be forward to the next state or not
	virtual bool handleEvent(const sf::Event& event) = 0;

protected:
	/// @brief Add state to the active stack when ready
	/// @param[in] stateID ID of the state to push
	/// @see StateStack::applyPendingChanges
	void requestStackPush(StatesID stateID);

	/// @brief Remove highest state from the active stack when ready
	/// @see StateStack::applyPendingChanges
	void requestStackPop();

	/// @brief Remove all states from the active stack when ready
	/// @see StateStack::applyPendingChanges
	void requestStackClear();

	//----------------------------------------

	/// @brief Get the current game context
	/// @return Current game context
	Context getContext() const;

private:
	/// @brief Pointer to the owning stack
	StateStack* m_stack;
	/// @brief Current game context
	Context m_context;
};
