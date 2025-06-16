# Makefile Sederhana untuk Proyek C dengan Raylib
# Disesuaikan untuk MinGW di Windows

#---[ 1. Konfigurasi Proyek ]--------------------------------------------------

# Compiler yang akan digunakan
CC = gcc

# Nama file executable yang akan dihasilkan
BIN_NAME = Guess-The-Animal.exe

#---[ 2. Konfigurasi File (Otomatis) ]----------------------------------------

# Direktori tempat file sumber (.c) berada
SRC_DIRS = . body

# Secara otomatis menemukan SEMUA file .c di direktori yang ditentukan
SOURCES = $(foreach dir,$(SRC_DIRS),$(wildcard $(dir)/*.c))

#---[ 3. Pengaturan Kompilasi ]------------------------------------------------

# Flag untuk compiler:
# -Wall : Tampilkan semua peringatan
# -g    : Sertakan informasi debug
# -Iheader: Beritahu compiler di mana mencari file header (.h)
CFLAGS = -Wall -g -Iheader -std=c11

# Library yang akan di-link:
# PERBAIKAN: Menautkan langsung ke file library untuk mengatasi "cannot find"
# -lopengl32, -lgdi32, -lwinmm adalah dependensi sistem yang dibutuhkan Raylib
LIBS = header/raylib.h body/libraylib.a -lopengl32 -lgdi32 -lwinmm

#---[ 4. Aturan Build ]-------------------------------------------------------

# Target Phony (bukan nama file, tetapi nama untuk sebuah perintah)
.PHONY: all clean run

# Aturan default: kompilasi dan buat executable
all: $(BIN_NAME)

# Aturan untuk membuat executable
$(BIN_NAME): $(SOURCES)
	@echo "--> Mengompilasi semua sumber menjadi: $(BIN_NAME)"
	$(CC) $(SOURCES) -o $(BIN_NAME) $(CFLAGS) $(LIBS)
	@echo "--> Build berhasil!"

# Aturan untuk menjalankan program
# Ini akan pertama-tama memastikan program sudah ter-compile, lalu menjalankannya.
run: all
	@echo "--> Menjalankan program..."
	@echo.
	./$(BIN_NAME)

# Aturan untuk membersihkan file hasil kompilasi
clean:
	@echo "--> Membersihkan file lama..."
	@del /F /Q $(subst /,\,$(BIN_NAME)) 2>nul || rm -f $(BIN_NAME)
