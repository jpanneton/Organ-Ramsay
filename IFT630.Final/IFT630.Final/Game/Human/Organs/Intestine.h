#pragma once

// Name: Intestine.h
// Author: Charles Denicourt
// Description: Intestine organ class

#include <Game/Human/Organs/Organ.h>

namespace Human
{
	/// @brief Human intestine (asynchronous)
	/// @author Jeremi Panneton
	/// @ingroup game
    class Intestine : public Organ
    {
    public:
		/// @brief Construct an intestine in its default state (not yet started)
		/// @param[in] body Body on which is attached the organ
        Intestine(Body& body);

		/// @see Organ::update
        void update(float fps) override;

		/// @see Organ::run
        void run() override;
    };
}