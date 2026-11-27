Fechando o Campeonato
Trabalho de Programação — IFES (Campus Serra).
Integrantes
Nome
Matrícula
(preencher)
(preencher)
(preencher, se houver dupla)
(preencher)

O que o programa faz
Lê times.csv e partidas.csv, apura V/E/D/GM/GS/S/PG de cada time, monta a classificação, imprime a tabela com o resumo do campeonato e grava classificacao.csv. Não tem menu nem interação.
Como executar
Requisitos: Linux com gcc e make.
make          # compila e gera o executável ./campeonato
./campeonato  # executa (times.csv e partidas.csv devem estar na pasta atual)
make clean    # remove os arquivos gerados
Para testar um cenário, copie o arquivo desejado para partidas.csv:
cp partidas_vazio.csv partidas.csv      # campeonato não iniciado
cp partidas_parcial.csv partidas.csv    # 20 de 45 partidas (mostra o Líder)
cp partidas_completo.csv partidas.csv   # 45 de 45 partidas (mostra o Campeão)
Estrutura do repositório
Makefile              compilação
main.c                programa principal (carga, apuração, classificação, relatório)
team.c / team.h       TAD Team
teamlist.c / .h       TAD TeamList
match.c / match.h     TAD Match
matchlist.c / .h      TAD MatchList
times.csv             times (entrada)
partidas.csv          partidas (entrada)
partidas_*.csv        cenários de teste
Principais TADs
Todos têm a struct definida no .c, acessada só pelas funções do .h.
Team: id, nome e as estatísticas (V, E, D, GM, GS). Tem team_record_result para registrar uma partida. Saldo e pontos são sempre calculados, nunca armazenados.
TeamList: lista duplamente encadeada de times, com tl_insert_sorted (inserção ordenada pela classificação) e tl_find (busca por id).
Match: uma partida (id, os dois times e os gols de cada um).
MatchList: lista encadeada de partidas, na ordem do arquivo.
Principais decisões
Classificação por inserção ordenada: cada time apurado é inserido, com tl_insert_sorted, numa nova lista que se mantém ordenada. O critério (PG, V, saldo, GM, menor ID) fica em ranks_before, em teamlist.c.
Sem liberação dupla: a lista ordenada guarda os mesmos ponteiros da original. Só a original libera os times (tl_free); a ordenada usa tl_free_shallow, que libera só os nós.
Empates no resumo: melhor ataque/defesa só trocam com valor estritamente melhor (vale o mais bem classificado); a maior goleada só troca com diferença estritamente maior (vale a primeira partida do arquivo).
Campeão ou Líder: "Campeão" só quando as 45 partidas (n·(n−1)/2) foram lidas.
Alinhamento com acentos: o preenchimento do nome é calculado por caracteres, não por bytes, para o "õ" de ESCorpiões não desalinhar a tabela.
Memória: tudo que é alocado é liberado no fim do programa.
