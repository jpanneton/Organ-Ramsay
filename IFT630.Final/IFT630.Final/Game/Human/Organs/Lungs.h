#pragma once

// Name: Lungs.h
// Author: Jérémi Panneton
// Description: Lungs organ class

#include <Game/Human/Organs/Organ.h>

namespace Human
{
	/// @brief Human lungs (asynchronous)
	/// @author Jeremi Panneton
	/// @ingroup game
    class Lungs : public Organ
    {
    public:
		/// @brief Construct lungs in their default state (not yet started)
		/// @param[in] body Body on which is attached the organ
        Lungs(Body& body);

		/// @see Organ::update
        void update(float fps) override;

		/// @see Organ::draw
        void draw() const override;

		/// @see Organ::run
        void run() override;

    private:
		/// @see Trachea texture
        sf::Sprite m_trachea;
    };
}