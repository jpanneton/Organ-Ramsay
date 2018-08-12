#pragma once

#include "Engine/ThreadSignaler.h"
#include <SFML/Graphics/Sprite.hpp>
#include <atomic>
#include <memory>
#include <thread>

namespace Human
{
    class Body;

	/// @brief Human organ
	/// @author Jeremi Panneton
	/// @ingroup game
    class Organ
    {
    public:
        using Ptr = std::unique_ptr<Organ>;

		/// @brief Construct an organ in its default state (not yet started)
		/// @param[in] body Body on which is attached the organ
        Organ(Body& body);

		/// @brief Virtual destructor (just in case)
        virtual ~Organ();

		/// @brief Update animation and visual stuff (if any)
		/// @param[in] fps Frame rate
        virtual void update(float fps) = 0;

		/// @brief Draw organ
        virtual void draw() const;

		/// @brief Start organ asynchronously
        void start();

		/// @brief Make the organ perform its action (once)
        void trigger();

		/// @brief Shutdown organ
        void shutdown();

    protected:
    	/// @brief Task to execute asynchronously
        virtual void run() = 0;

		//========================================

		/// @brief Body on which is attached the organ
        Body& m_body;
		/// @brief Signaler that allows communication between different organs
        ThreadSignaler m_signaler;
		/// @brief If the organ is active or not
        std::atomic_bool m_running;
		/// @brief Organ texture
        sf::Sprite m_sprite;

    private:
		/// @brief Thread that allows asynchronous execution of the task defined in Organ::run()
        std::thread m_thread;
    };
}