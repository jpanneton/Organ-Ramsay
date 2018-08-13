#pragma once

// Name: Liver.h
// Author: Jérémi Panneton
// Description: Liver organ class

#include <Game/Human/Organs/Organ.h>

namespace Human
{
	/// @brief Human liver (display only)
	/// @author Jeremi Panneton
	/// @ingroup game
    class Liver : public Organ
    {
    public:
		/// @brief Construct lungs in their default state (not yet started)
		/// @param[in] body Body on which is attached the organ
        Liver(Body& body);

		/// @see Organ::run
        void run() override;
    };
}