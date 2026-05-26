#include <iostream>
#include <string>
#include <vector>
#include "Trie.hpp"
#include "GamesDatabase.hpp"

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        std::cout << "Usage: ./app k prefix\n";
        return 1;
    }

    int k = std::stoi(argv[1]);
    std::string prefix = argv[2];

    Trie trie;

    for (int i = 0; i < numberOfGames; i++)
    {
        trie.insert(&games[i]);
    }

    std::vector<Game *> games = trie.autocomplete(prefix, k);

    if (games.empty())
        std::cout << "No results found\n";

    else
    {
        for (int i = 0; i < games.size(); i++)
        {
            std::cout << std::endl
                      << games[i]->getTitle() << " | "
                      << games[i]->getShortDescription() << " | "
                      << games[i]->getPopularity() << std::endl;
        }
    }

    return 0;
}