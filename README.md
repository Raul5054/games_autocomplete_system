# Sistema de Autocomplete de Jogos
## Descrição do projeto
Este projeto implementa um sistema de autocomplete e recomendação de jogos baseado em prefixos. A estrutura principal 
de dados utilizada é uma Trie (Árvore de Prefixos), projetada para armazenar títulos de jogos e otimizar buscas 
de forma insensível a maiúsculas/minúsculas e espaços em branco. O sistema retorna os resultados ordenados pela popularidade 
do jogo e, em caso de empate, pela ordem alfabética da chave de busca.

## Funcionalidades
- Inserir jogos na base de busca extraindo os dados (título, descrição curta e popularidade) de um banco de dados global.
- Buscar nomes de jogos utilizando prefixos, convertendo automaticamente letras maiúsculas para minúsculas e ignorando espaços em branco.
- Executar uma coleta dinâmica que retorna até `k` resultados para o prefixo pesquisado.
- Ordenar os resultados automaticamente com base na popularidade (ordem decrescente) e, em caso de empate, pela ordem alfabética da chave de busca.

## Estruturas Usadas
- ``TrieNode``: armazena cada caractere da árvore, contendo um array de ponteiros para os próximos nós (`children`), uma flag booleana `isEndOfTitle`
para demarcar o fim de uma palavra, e um ponteiro para o objeto `Game` correspondente.
- ``DFS (Busca em Profundidade)``: navega pela subárvore a partir do final do prefixo pesquisado, recolhendo os ponteiros de todos os jogos válidos
encontrados no caminho.
- ``Selection Sort``: algoritmo de ordenação implementado in-place para organizar os resultados filtrados respeitando a regra de popularidade e o
desempate alfabético da chave de busca.
