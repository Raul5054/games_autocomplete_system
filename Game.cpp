#include "Game.hpp"
#include <string>

Game::Game()
{
    title = "";
    shortDescription = "";
    popularity = 0;
}

Game::Game(std::string title, std::string shortDescription, int popularity)
{
    this->title = title;
    this->shortDescription = shortDescription;
    this->popularity = popularity;
}

Game::~Game() {}

std::string Game::getTitle()
{
    return title;
}

std::string Game::getShortDescription()
{
    return shortDescription;
}

int Game::getPopularity()
{
    return popularity;
}