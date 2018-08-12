#include "Game/Application.h"
#include <iostream>

int main()
{
    try
    {
        Application game;
        game.run();
    }
    catch (const std::exception& e)
    {
        std::cout << "Exception: " << e.what() << std::endl;
    }
}