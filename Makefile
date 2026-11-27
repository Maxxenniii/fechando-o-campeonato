# Compilador e opções
CC = gcc
CFLAGS = -Wall -Wextra -std=c11

# Arquivos-fonte, objetos e executável
SRCS = main.c team.c teamlist.c match.c matchlist.c
OBJS = $(SRCS:.c=.o)
TARGET = campeonato

.PHONY: all run clean

# Alvo padrão: compila
all: $(TARGET)

# Compila (se preciso) e executa
run: $(TARGET)
	./$(TARGET)

# Liga os objetos no executável
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS)

# Compila cada .c em .o; recompila se algum .h mudar
%.o: %.c $(wildcard *.h)
	$(CC) $(CFLAGS) -c $< -o $@

# Remove arquivos gerados
clean:
	rm -f $(OBJS) $(TARGET) classificacao.csv
