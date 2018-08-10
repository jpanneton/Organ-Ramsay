#pragma once

// Name: ResourceIdentifiers.h
// Author: Jérémi Panneton
// Description: Resource identifiers

#include "Engine/ResourceHolder.h"

/************** Forward declarations **************/

// SFML classes
namespace sf
{
	class Font;
	class Texture;
}

/************** Resource identifiers **************/

// Fonts
enum class FontsID
{
	Main
};

// Textures
enum class TexturesID
{
	ButtonNormal,
	ButtonSelected,
	ButtonPressed,
    HumanBody,
    HumanBrain,
    HumanHeart,
    HumanLungs,
    HumanLungsTrachea,
    HumanStomach,
    HumanLiver,
    HumanIntestine
};

using FontHolder = ResourceHolder<sf::Font, FontsID>;
using TextureHolder = ResourceHolder<sf::Texture, TexturesID>;