#ifndef TRIE_HPP
#define TRIE_HPP
#include <string>
#include <vector>
#include "Game.hpp"

// o tamanho é 26 letras + 10 números = 36
const int ALPHABET_SIZE = 36;

class TrieNode
{

public:
    TrieNode *children[ALPHABET_SIZE];
    bool isEndOfTitle;
    Game *game;

    TrieNode();
    ~TrieNode();
};

class Trie
{

private:
    TrieNode *root;

public:
    Trie();
    ~Trie();

    bool insert(Game *game);
    bool contains(std::string title);

    std::vector<Game *> autocomplete(std::string prefix, int k);

    std::string toSearchKey(std::string text);
    void sortResults(std::vector<Game *> &games);
    int getIndex(char c);
    void dfs(TrieNode *subroot, std::vector<Game *> &games);
    // Outros métodos auxiliares, se necessário
};

#endif