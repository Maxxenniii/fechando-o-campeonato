# Fechando o Campeonato

Projeto desenvolvido em linguagem C para o trabalho de Programação do Instituto Federal do Espírito Santo (IFES), Campus Serra.

O programa realiza a leitura dos arquivos CSV com os dados dos times e das partidas de um campeonato de futebol. A partir desses dados, calcula as estatísticas de cada equipe, organiza a tabela de classificação e apresenta um resumo com os principais resultados do campeonato.

## Integrantes

| Nome | Matrícula |
|---|---|
| Maxine Amorim Silva Gois | 20252bsi0305 |
| Davi Terra Vieira da Silva | 20252bsi0097 |

## Funcionalidades

- Leitura dos times a partir do arquivo `times.csv`.
- Leitura das partidas a partir do arquivo `partidas.csv`.
- Cálculo de vitórias, empates e derrotas.
- Cálculo de gols marcados e gols sofridos.
- Cálculo do saldo de gols e dos pontos ganhos.
- Classificação dos times conforme os critérios de desempate.
- Identificação do campeão ou líder do campeonato.
- Identificação do melhor ataque e da melhor defesa.
- Identificação da maior goleada.
- Geração do arquivo `classificacao.csv` com a tabela final.

## Organização do projeto

O projeto foi dividido em quatro TADs (Tipos Abstratos de Dados), além do programa principal:

- **Team:** responsável pelos dados e pelas estatísticas de cada time.
- **TeamList:** responsável pelo armazenamento e gerenciamento dos times por meio de uma lista duplamente encadeada.
- **Match:** representa uma partida, armazenando os times envolvidos e os gols marcados.
- **MatchList:** responsável pelo armazenamento e gerenciamento das partidas por meio de uma lista encadeada.
- **main.c:** responsável por executar as etapas do programa, realizar a leitura dos arquivos, atualizar as estatísticas, organizar a classificação e gerar o relatório.

## Critérios de classificação

A classificação dos times segue os seguintes critérios, nesta ordem:

1. Maior número de pontos ganhos (PG).
2. Maior número de vitórias (V).
3. Maior saldo de gols (S).
4. Maior número de gols marcados (GM).
5. Menor ID.

A pontuação é calculada da seguinte forma:

- Vitória: 3 pontos.
- Empate: 1 ponto.
- Derrota: 0 pontos.

## Como executar

É necessário ter o GCC e o Make instalados em um ambiente Linux.

1. Clone o repositório:

```bash
git clone URL_DO_REPOSITORIO
```

2. Entre na pasta do projeto:

```bash
cd NOME_DA_PASTA
```

3. Compile o programa:

```bash
make
```

4. Execute:

```bash
./campeonato
```

O programa utiliza os arquivos `times.csv` e `partidas.csv`, que devem estar disponíveis no diretório esperado pela implementação.

## Arquivos de saída

Ao finalizar a execução, o programa apresenta no terminal:

- Tabela de classificação dos times.
- Quantidade de partidas disputadas.
- Campeão ou líder do campeonato.
- Melhor ataque.
- Melhor defesa.
- Maior goleada.

Também é gerado o arquivo `classificacao.csv`, contendo a tabela de classificação organizada.

## Tecnologias utilizadas

- Linguagem C.
- GCC.
- Make.
- Arquivos CSV.
- Listas encadeadas.
- Alocação dinâmica de memória.
