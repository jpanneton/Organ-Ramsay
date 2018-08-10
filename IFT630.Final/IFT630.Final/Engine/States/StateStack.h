#pragma once

// Name: StateStack.h
// Author: Jérémi Panneton
// Description: State stack class

#include "Engine/States/State.h"
#include "Game/States/StateIdentifiers.h"
#include <SFML/System/NonCopyable.hpp>
#include <SFML/System/Time.hpp>
#include <functional>
#include <unordered_map>
#include <vector>

/// @brief State container and manager
/// @author Jeremi Panneton
/// @ingroup engine
class StateStack : sf::NonCopyable
{
public:
	/// @brief Stack actions available to states
	enum Action
	{
		Push,
		Pop,
		Clear,
	};

	//========================================

	/// @brief Construct an empty stack
	/// @param[in] context Current game context
	explicit StateStack(State::Context context);
	
	/// @brief Register a new state
	/// @tparam StateType Type of the derived state
	/// @param[in] stateID ID of the state to register
	/// @attention The registered state is not yet created!
	/// @see StateStack::createState
	template<typename T>
	void registerState(StatesID stateID);

	//----------------------------------------
	
	/// @brief Update all states in the active stack
	/// @param[in] dt Elapsed time since last update
	void update(sf::Time dt);

	/// @brief Draw all elements that need to be drawn in each active states
	void draw();

	/// @brief Forward occured event to each active states for handling
	/// @param[in] event Input event
	void handleEvent(const sf::Event& event);

	//----------------------------------------
	
	/// @brief Add state to the active stack
	/// @param[in] stateID ID of the state to push
	void pushState(StatesID stateID);

	/// @brief Remove highest state from the active stack
	void popState();

	/// @brief Remove all states from the active stack
	void clearStates();
	
	/// @brief Check if there are no states in the stack
	/// @return If the stack is empty or not
	bool isEmpty() const;

private:
	/// @brief Instantiate a registered state
	/// @param[in] stateID ID of the state to create
	/// @return Pointer to the newly created state object
	/// @attention The state needs to be registered first!
	/// @see StateStack::registerState
	State::Ptr createState(StatesID stateID);

	/// @brief Execute all external state requests (like push, pop and clear)
	void applyPendingChanges();

	//========================================

	/// @brief State request (action to perform)
	/// @author Jeremi Panneton
	struct PendingChange
	{
		/// @brief Create an action to perform in the near future
		/// @param[in] action Action to perform
		/// @param[in] stateID ID of the requesting state
		explicit PendingChange(Action action, StatesID stateID = StatesID::None);
		
		/// @brief Action to perform
		Action action;
		/// @brief Requesting state
		StatesID stateID;
	};
	
	//========================================

	/// @brief Stack of created states (main container)
	std::vector<State::Ptr> m_stack;
	/// @brief External state requests (actions to perform)
	std::vector<PendingChange> m_pendingList;
	
	/// @brief Current game context
	State::Context m_context;
	/// @brief Registered states (ready to be created)
	std::unordered_map<StatesID, std::function<State::Ptr()>> m_factories;
};

template<typename StateType>
void StateStack::registerState(StatesID stateID)
{
	m_factories[stateID] = [this]()
	{
		return State::Ptr{ std::make_unique<StateType>(*this, m_context) };
	};
}