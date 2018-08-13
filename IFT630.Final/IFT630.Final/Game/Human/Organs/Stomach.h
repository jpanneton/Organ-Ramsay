#pragma once

// Name: Stomach.h
// Author: Charles Denicourt
// Description: Stomach organ class

#include <Game/Human/Organs/Organ.h>

namespace Human
{
	/// @brief Human stomach (asynchronous)
	/// @author Jeremi Panneton
	/// @ingroup game
    class Stomach : public Organ
    {
    public:
		/// @brief Construct a stomach in its default state (not yet started)
		/// @param[in] body Body on which is attached the organ
        Stomach(Body& body);

		/// @see Organ::run
        void run() override;
    };
}