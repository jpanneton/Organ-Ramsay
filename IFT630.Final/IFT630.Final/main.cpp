#include "Game/Application.h"
#include <iostream>

int main()
{
    try
    {
        Application game;
        game.run();
    }
    catch (std::exception& e)
    {
        std::cout << "Exception: " << e.what() << std::endl;
    }
}