#include "Utilities.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <thread>

namespace Util
{
    void zoomViewAt(sf::RenderWindow& window, sf::View& view, const sf::Vector2i& position, float zoomAmount)
    {
        window.setView(view);
        const sf::Vector2f beforeCoord = window.mapPixelToCoords(position);
        view.zoom(zoomAmount);
        window.setView(view);
        const sf::Vector2f afterCoord = window.mapPixelToCoords(position);
        const sf::Vector2f offsetCoords = beforeCoord - afterCoord;
        view.move(offsetCoords);
        window.setView(view);
    }

	float normalDist(float x, float mean, float std)
	{
		return exp(-0.5f * pow(x - mean, 2) / pow(std, 2)) / (std * sqrt(2.f * pi<float>()));
	}

	void sleep(long long duration)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(duration));
	}
}
