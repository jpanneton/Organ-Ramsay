#pragma once

#include <Game/Human/Organs/Organ.h>

namespace Human
{
	/// @brief Human liver
	/// @author Jeremi Panneton
	/// @ingroup game
    class Liver : public Organ
    {
    public:
		/// @brief Construct lungs in their default state (not yet started)
		/// @param[in] body Body on which is attached the organ
        Liver(Body& body);

		/// @see Organ::update
        void update(float fps) override;

		/// @see Organ::run
        void run() override;
    };
}