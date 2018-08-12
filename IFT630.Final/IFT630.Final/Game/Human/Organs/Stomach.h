#pragma once

#include <Game/Human/Organs/Organ.h>

namespace Human
{
	/// @brief Human stomach
	/// @author Jeremi Panneton
	/// @ingroup game
    class Stomach : public Organ
    {
    public:
		/// @brief Construct a stomach in its default state (not yet started)
		/// @param[in] body Body on which is attached the organ
        Stomach(Body& body);

		/// @see Organ::update
        void update(float fps) override;

		/// @see Organ::run
        void run() override;
    };
}