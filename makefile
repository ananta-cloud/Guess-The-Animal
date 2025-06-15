#==============================================================================
# Makefile for Guess-The-Animal C Project
#==============================================================================

# 1. Variabel yang Dapat Dikonfigurasi
#==============================================================================

# Compiler C
CC := gcc

# Nama file eksekusi akhir
TARGET_NAME := guess_animal

# Direktori
SRCDIR_BODY := body
SRCDIR_ROOT := .
HEADERDIR   := header
OBJDIR      := obj
TARGETDIR   := dist

# Flags untuk compiler
# -Wall: Menampilkan semua peringatan (praktik terbaik)
# -g: Menyertakan informasi debug untuk GDB
# -I$(HEADERDIR): Memberi tahu compiler di mana mencari file header (.h)
CFLAGS := -Wall -g -I$(HEADERDIR)

# Flags untuk linker (jika Anda perlu menautkan library seperti -lm)
LDFLAGS :=

#==============================================================================
# Otomatisasi Pencarian File
#==============================================================================

# Menemukan semua file .c di direktori body dan main.c di root
SOURCES := $(wildcard $(SRCDIR_BODY)/*.c) $(SRCDIR_ROOT)/main.c

# Membuat daftar file objek (.o) yang sesuai, menempatkannya di OBJDIR
# Contoh: body/utils.c -> obj/utils.o
OBJECTS := $(patsubst $(SRCDIR_BODY)/%.c,$(OBJDIR)/%.o,$(filter %body/%.c,$(SOURCES)))
OBJECTS += $(patsubst $(SRCDIR_ROOT)/%.c,$(OBJDIR)/%.o,$(filter %main.c,$(SOURCES)))

# File eksekusi akhir dengan path lengkap
TARGET := $(TARGETDIR)/$(TARGET_NAME)

# VPATH memberitahu 'make' di mana harus mencari file sumber
VPATH = $(SRCDIR_BODY):$(SRCDIR_ROOT)

#==============================================================================
# Aturan (Rules) Makefile
#==============================================================================

# Aturan default: yang pertama kali dijalankan saat mengetik 'make'
all: $(TARGET)

# Aturan untuk menautkan (linking) semua file objek menjadi file eksekusi akhir
$(TARGET): $(OBJECTS)
	@mkdir -p $(TARGETDIR)
	@echo "LD   $(notdir $@)"
	$(CC) $(OBJECTS) -o $@ $(LDFLAGS)
	@echo "Build successful! Executable is at $(TARGET)"

# Aturan pola untuk mengkompilasi file .c menjadi file objek .o
# Ini menangani file dari direktori manapun yang didefinisikan di VPATH
$(OBJDIR)/%.o: %.c
	@mkdir -p $(OBJDIR)
	@echo "CC   $<"
	$(CC) $(CFLAGS) -c $< -o $@

# Aturan untuk membersihkan file hasil build
clean:
	@echo "Cleaning up project..."
	@rm -rf $(OBJDIR) $(TARGETDIR)
	@echo "Cleanup complete."

# Aturan untuk membangun ulang proyek (bersihkan lalu bangun lagi)
re: clean all

# Aturan untuk menjalankan program setelah kompilasi
run: all
	@echo "Running the application..."
	./$(TARGET)

#==============================================================================
# Phony Targets (Target yang bukan nama file)
#==============================================================================
.PHONY: all clean re run