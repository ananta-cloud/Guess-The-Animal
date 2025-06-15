# Makefile Sederhana untuk Proyek C/C++
# Versi ini tidak membuat direktori atau file perantara (.o).

#---[ 1. Konfigurasi Proyek ]--------------------------------------------------

# Compiler yang akan digunakan
CC = gcc

# Nama file executable yang akan dihasilkan
BIN_NAME = Game.exe

#---[ 2. Konfigurasi File (Otomatis) ]----------------------------------------

# Direktori tempat file sumber (.c) berada
SRC_DIRS = . body

# Secara otomatis menemukan SEMUA file .c di direktori yang ditentukan
SOURCES = $(foreach dir,$(SRC_DIRS),$(wildcard $(dir)/*.c))

#---[ 3. Pengaturan Kompilasi ]------------------------------------------------

# Flag untuk compiler
CFLAGS = -Wall -g -Iheader -std=c11

# Library yang akan di-link (jika ada)
LIBS =

#---[ 4. Aturan Build ]-------------------------------------------------------

# Target Phony (bukan nama file, tetapi nama untuk sebuah perintah)
.PHONY: all clean run

# Aturan default: kompilasi dan buat executable
all: $(BIN_NAME)

# Aturan untuk membuat executable dalam satu langkah tunggal
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

# Aturan untuk membersihkan proyek
clean:
	@echo "--> Membersihkan proyek..."
	-rm -f $(BIN_NAME)
	@echo "--> Pembersihan selesai."
