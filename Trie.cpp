#include "Trie.hpp"
#include <string>
#include <cctype>

TrieNode::TrieNode()
{
    isEndOfTitle = false;
    game = nullptr;

    for (int i = 0; i < ALPHABET_SIZE; i++)
    {
        children[i] = nullptr;
    }
}

TrieNode::~TrieNode()
{
    for (int i = 0; i < ALPHABET_SIZE; i++)
    {
        if (children[i] != nullptr)
        {
            delete children[i];
        }
    }
}

Trie::Trie()
{
    root = new TrieNode;
}

Trie::~Trie()
{
    if (root != nullptr)
    {
        delete root;
    }
}

std::string Trie::toSearchKey(std::string text)
{
    std::string key = "";

    for (char c : text)
    {
        // transforma letras maiúsculas para minúsculas
        if (c >= 'A' && c <= 'Z')
        {
            key += std::tolower(c);
        }

        // ignora espaçoes
        else if (c == ' ')
        {
            continue;
        }

        // se for número ou se já for minúscula
        else
        {
            key += c;
        }
    }

    return key;
}

// retorna o índice usando a tabela ASCII
int Trie::getIndex(char c)
{
    if (c >= 'a' && c <= 'z')
    {
        return c - 'a';
    }

    if (c >= '0' && c <= '9')
    {
        return c - '0' + 26;
    }

    return -1;
}

bool Trie::insert(Game *game)
{
    if (game == nullptr)
        return false;

    std::string title = game->getTitle();
    std::string key = toSearchKey(title);

    TrieNode *current = root;
    for (char c : key)
    {
        int i = getIndex(c);
        if (current->children[i] == nullptr)
        {
            current->children[i] = new TrieNode();
        }

        current = current->children[i];
    }

    current->isEndOfTitle = true;
    current->game = game;

    return true;
}

bool Trie::contains(std::string title)
{
    // noramliza o título
    std::string key = toSearchKey(title);

    // percorre a trie
    TrieNode *current = root;
    for (char c : key)
    {
        int i = getIndex(c);
        // se o children for nullptr significa que não contém o título na trie
        if (current->children[i] == nullptr)
            return false;
    }

    // se não achou um nullptr, significa que chegou a um resultado, mas pode ser apenas parte
    // de outro título, por isso verifica o isEndOfTitle
    return current->isEndOfTitle;
}

// selectionSort pela simplicidade
void Trie::sortResults(std::vector<Game *> &games)
{
    int n = games.size();
    // não precisa ordernar se só tiver um elemento ou nenhum
    if (n == 0 || n == 1)
        return;

    for (int i = 0; i < n; i++)
    {
        int big_idx = i;

        for (int j = i + 1; j < n; j++)
        {
            // ordena pela popularidade
            if (games[big_idx]->getPopularity() < games[j]->getPopularity())
            {
                big_idx = j;
            }

            // ordena pela ordem alfabética
            if (games[big_idx]->getPopularity() == games[j]->getPopularity())
            {
                std::string key_j = toSearchKey(games[j]->getTitle());
                std::string key_big = toSearchKey(games[big_idx]->getTitle());

                if (key_big > key_j)
                {
                    big_idx = j;
                }
            }
        }

        // faz a troca
        if (big_idx != i)
        {
            Game *temp = games[big_idx];
            games[big_idx] = games[i];
            games[i] = temp;
        }
    }
}

void Trie::dfs(TrieNode *subroot, std::vector<Game *> &games)
{
    if (subroot == nullptr)
        return;

    if (subroot->isEndOfTitle == true)
    {
        games.push_back(subroot->game);
    }

    for (int i = 0; i < ALPHABET_SIZE; i++)
    {
        if (subroot->children[i] != nullptr)
        {
            dfs(subroot->children[i], games);
        }
    }
}

std::vector<Game *> Trie::autocomplete(std::string prefix, int k)
{
    // verifica o tamanho de k
    if (k <= 0)
        return std::vector<Game *>();

    std::string key = toSearchKey(prefix);
    TrieNode *current = root;

    // encontra o fim do prefixo e início da subárvore
    for (char c : key)
    {
        int i = getIndex(c);
        if (current->children[i] == nullptr)
        {
            return std::vector<Game *>();
        }

        current = current->children[i];
    }

    std::vector<Game *> games;
    dfs(current, games);

    sortResults(games);

    int lim = games.size();
    if (k < lim)
        lim = k;

    std::vector<Game *> games_k;
    for (int i = 0; i < lim; i++)
    {
        games_k.push_back(games[i]);
    }

    return games_k;
}