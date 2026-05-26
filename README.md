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

## Compilação
Para compilar, utilize o comando:
```bash
g++ main.cpp Game.cpp Trie.cpp GamesDatabase.cpp -o app
```

## Execução
Para executar, utilize o comando passando o limite de resultados k e o prefixo desejado (utilize aspas para prefixos com espaços):
```bash
./app k prefixo
```

# Testes (Casos de Sucessos)
### Teste 1 (prefixo simples)
- comando
```bash
./app 1 cou
```

- saída esperada:
```bash
Counter Strike Global Offensive | Counter Strike Global Offensive CS GO expands upon the team based action gameplay that it pioneered
when it was launched 19 years ago CS GO features new maps characters weapons and game modes and delivers updated versions of the
classic CS content de dust2 etc | 7428921
```

### Teste 2 (prefixo com espaços em brancos e letras maiúsculas)
- comando
```bash
./app 2 "Half l"
```

- saída esperada:
```bash
Half Life 2 | 1998 HALF LIFE sends a shock through the game industry with its combination of pounding action and continuous immersive
storytelling Valve s debut title wins more than 50 game of the year awards on its way to being named Best PC Game Ever by PC Gamer
and launches a franchise with more than eight million retail units sold worldwide | 131995

Half Life Alyx | Half Life Alyx is Valve s VR return to the Half Life series It s the story of an impossible fight against a vicious
alien race known as the Combine set between the events of Half Life and Half Life 2 Playing as Alyx Vance you are humanity s only
chance for survival | 71194
```

### Teste 3 (limitação do tamanho de `k`)
- comando
```bash
./app 1 the
```

- saída esperada:
```bash
The Witcher 3 Wild Hunt | You are Geralt of Rivia mercenary monster slayer Before you stands a war torn monster infested continent you
can explore at will Your current contract Tracking down Ciri the Child of Prophecy a living weapon that can alter the shape of the world | 666080
```

### Teste 4 (caso de empate)
- comando
```bash
./app 3 "Grand Theft Auto" 
```

- saída esperada:
```bash
Grand Theft Auto V | Grand Theft Auto V for PC offers players the option to explore the award winning world of Los Santos and Blaine County
in resolutions of up to 4k and beyond as well as the chance to experience the game running at 60 frames per second | 1472644

Grand Theft Auto IV Complete Edition | PLEASE NOTE Microsoft no longer supports creating Games for Windows LIVE accounts within Grand Theft
Auto IV You can create an account through account xbox com and then log into your account in game This standalone retail title spans three distinct
stories interwoven to create one of the most unique and engaging single player | 112673

Grand Theft Auto IV The Complete Edition | Niko Bellic Johnny Klebitz and Luis Lopez all have one thing in common they live in the worst city in
America Liberty City worships money and status and is heaven for those who have them and a living nightmare for those who don t | 112673
```
Perceba que `Grand Theft Auto IV Complete Edition` e `Grand Theft Auto IV The Complete Edition` tem a mesma popularidade, mas pela ordem alfabética
`c` vem antes de `t`, logo a versão sem o `The` vem primeiro.

## Testes (Casos de Falhas)
### Teste 5 (prefixo inexistente)
- comando
```bash
./app 4 xcr
```

- saída esperada:
```bash
No results found
```

### Teste 6 (argumentos inválidos)
- comando
```bash
./app 3
```

- saída esperada:
```bash
Usage: ./app k prefix
```

## Autores
- Raul Medici Martinelli
- Pablo Levy Fernandes Alcântara
