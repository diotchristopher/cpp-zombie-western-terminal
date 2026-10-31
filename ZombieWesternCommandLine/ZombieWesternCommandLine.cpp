// ZombieWesternCommandLine.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

// cpp
#include <iostream>

#ifdef _WIN32
#define NOMINMAX
#include <windows.h>
#endif

// game
#include "../public/Player.h"
#include "../public/Game.h"

int main()
{
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
#endif
    Game game("Elias"); // óublie du constructeur
    game.run();
    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
