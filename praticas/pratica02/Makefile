CC = gcc
CFLAGS = -Wall -Wextra -std=c99
OBJ = main.o busca_largura.o busca_profundidade.o
TARGET = pratica02

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o $(TARGET)

.PHONY: all clean