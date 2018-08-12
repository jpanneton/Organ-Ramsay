#pragma once

#include <Game/Human/Organs/Organ.h>

namespace Human
{
	/// @brief Human heart
	/// @author Jeremi Panneton
	/// @ingroup game
    class Heart : public Organ
    {
    public:
		/// @brief Construct an heart in its default state (not yet started)
		/// @param[in] body Body on which is attached the organ
        Heart(Body& body);

		/// @see Organ::update
        void update(float fps) override;

		/// @see Organ::run
        void run() override;
    };
}