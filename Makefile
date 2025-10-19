# ==========================================
# Makefile dla projektu "Pomiar odczytu pliku"
# ==========================================

CC = gcc
CFLAGS = -O2 -Wall -std=c11 -Iinclude
LDFLAGS = -lrt
TARGET = lab1

SRC_DIR = src
OBJ_DIR = obj

SRC = $(wildcard $(SRC_DIR)/*.c)
OBJ = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC))

# Domyślny cel
all: $(TARGET)

# Kompilacja programu
$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $@ $(LDFLAGS)

# Kompilacja plików .c do .o
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Tworzenie katalogu na pliki obiektowe
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Czyszczenie projektu
clean:
	rm -rf $(OBJ_DIR) $(TARGET)

# Czyszczenie wszystkich śmieci
distclean: clean
	rm -f *~ core

.PHONY: all clean distclean
