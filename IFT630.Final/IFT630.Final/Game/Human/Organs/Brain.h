#pragma once

// Name: Brain.h
// Author: Jérémi Panneton
// Description: Brain organ class

#include <Game/Human/Organs/Organ.h>

namespace Human
{
	/// @brief Human brain (synchronous)
	/// @author Jeremi Panneton
	/// @ingroup game
    class Brain : public Organ
    {
    public:
		/// @brief Construct a brain in its default state (not yet started)
		/// @param[in] body Body on which is attached the organ
        Brain(Body& body);

		/// @see Read body data and trigger organs
		/// @param[in] fps Frame rate
        void update(float fps) override;

		/// @brief Task to execute asynchronously (none here)
        void run() override;

    private:
		/// @see Trigger heart or not
		/// @param[in] fps Frame rate
        bool updateHeart(float fps);

		/// @see Trigger lungs or not
		/// @param[in] fps Frame rate
        bool updateLungs(float fps);

		/// @see Trigger stomach or not
		/// @param[in] fps Frame rate
	    bool updateStomach(float fps);

		/// @see Trigger intestine or not
		/// @param[in] fps Frame rate
	    bool updateIntestine(float fps);

		/// @see Update happiness level based on other body informations
		void updateHappiness();
    };
}