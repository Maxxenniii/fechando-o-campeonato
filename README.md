# Fechando o Campeonato

Este projeto implementa um sistema de apuração e classificação do Campeonato Computacional de Futebol utilizando a linguagem C. O programa realiza a leitura dos times e dos resultados das partidas armazenados em arquivos CSV, calcula as estatísticas de cada equipe, organiza a tabela de classificação e apresenta um resumo com os principais resultados do campeonato.

A implementação utiliza Tipos Abstratos de Dados (TADs), listas encadeadas e alocação dinâmica de memória para organizar e manipular as informações. Todo o processamento acontece automaticamente, sem interação com o usuário.

---

## Integrantes

| Nome | Matrícula |
|---|---|
| Maxine Amorim Silva Gois | 20252bsi0305 |
| Davi Terra Vieira da Silva | 20252bsi0097 |

---

## Estrutura do Repositório

```text
├── Makefile             # Automação da compilação
├── README.md            # Documentação do projeto
├── main.c               # Programa principal
│
├── team.c / team.h      # TAD de times e estatísticas
├── teamlist.c / teamlist.h  # TAD de lista de times
│
├── match.c / match.h    # TAD de partidas
├── matchlist.c / matchlist.h # TAD de lista de partidas
│
├── times.csv            # Dados dos times
├── partidas.csv         # Resultados utilizados na execução
├── partidas_vazio.csv   # Cenário sem partidas disputadas
├── partidas_parcial.csv # Cenário com 20 partidas
├── partidas_completo.csv # Cenário com 45 partidas
```

### Sobre os arquivos

- **Makefile:** responsável pela compilação dos arquivos do projeto. Possui os seguintes comandos:
  - `make`: compila o programa e gera o executável `campeonato`.
  - `make run`: compila, se necessário, e executa o programa.
  - `make clean`: remove os arquivos objeto, o executável e o arquivo `classificacao.csv`.

- **main.c:** contém o fluxo principal do programa. É responsável por carregar os dados dos arquivos CSV, apurar as estatísticas, organizar a classificação, imprimir o relatório e gerar o arquivo final.

- **team.c / team.h:** implementam o TAD `Team`, responsável por armazenar os dados e as estatísticas de cada equipe.

- **teamlist.c / teamlist.h:** implementam o TAD `TeamList`, responsável pelo gerenciamento dos times utilizando uma lista duplamente encadeada.

- **match.c / match.h:** implementam o TAD `Match`, que representa uma partida e armazena seu identificador, os times envolvidos e os gols de cada equipe.

- **matchlist.c / matchlist.h:** implementam o TAD `MatchList`, responsável pelo armazenamento das partidas em uma lista encadeada.

- **times.csv:** contém os identificadores e nomes dos dez times participantes do campeonato.

- **partidas.csv:** contém os resultados das partidas que serão utilizados durante a execução.

- **partidas_vazio.csv, partidas_parcial.csv e partidas_completo.csv:** arquivos disponibilizados para testar diferentes situações do campeonato.

---

## TADs utilizados

### 1. Team

O TAD `Team`, definido em `team.h` e implementado em `team.c`, representa cada equipe participante do campeonato.

Sua estrutura armazena as seguintes informações:

- `id`: identificador do time.
- `name`: nome da equipe.
- `wins`: quantidade de vitórias.
- `draws`: quantidade de empates.
- `losses`: quantidade de derrotas.
- `goals_scored`: quantidade de gols marcados.
- `goals_conceded`: quantidade de gols sofridos.

Entre suas principais funções estão:

- `team_create()`: cria um time com seu identificador e nome.
- `team_record_result()`: registra o resultado de uma partida e atualiza
