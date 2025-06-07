#include "utils.h"

void print_separator() {
    printf("==================================================\n");
}

void print_header(const char* title) {
    print_separator();
    printf("          %s\n", title);
    print_separator();
}

void print_main_menu() {
    print_header("ANIMAL GUESSING GAME - MENU UTAMA");
    printf("1. Mulai Permainan Single Player\n");
    printf("2. Mulai Permainan Multiplayer\n");
    printf("3. Lihat Riwayat Permainan\n");
    printf("4. Menu Admin\n");
    printf("5. Keluar\n");
    print_separator();
    printf("Pilih menu (1-5): ");
}

void print_game_menu() {
    print_header("MENU PERMAINAN");
    printf("1. Main Sekali\n");
    printf("2. Main Terus-menerus\n");
    printf("3. Kembali ke Menu Utama\n");
    print_separator();
    printf("Pilih opsi (1-3): ");
}

void print_admin_menu() {
    print_header("MENU ADMIN");
    printf("1. Undo Operasi Terakhir\n");
    printf("2. Kembali ke Menu Utama\n");
    print_separator();
    printf("Pilih opsi (1-2): ");
}

int get_menu_choice(int max_choice) {
    char input[10];
    int choice;
    
    while (1) {
        if (fgets(input, sizeof(input), stdin) != NULL) {
            choice = atoi(input);
            if (choice >= 1 && choice <= max_choice) {
                return choice;
            }
        }
        printf("Pilihan tidak valid! Masukkan angka 1-%d: ", max_choice);
    }
}

void print_welcome() {
    system("clear || cls"); // Membersihkan layar konsol
    print_header("SELAMAT DATANG DI ANIMAL GUESSING GAME!");
    printf("Pikirkan seekor hewan, dan saya akan mencoba menebaknya!\n\n");
}

void print_goodbye() {
    print_header("TERIMA KASIH TELAH BERMAIN!");
}

void ready() {
    printf("\nTekan ENTER untuk melanjutkan...");
    getchar();
}

int play_again() {
    printf("\nApakah Anda ingin bermain lagi? ");
    int answer = get_answer();
    
    if (answer == 1) {
        printf("Asyik! Mari bermain lagi!\n\n");
        return 1;
    }
    return 0;
}

/**
 * @brief Menginisialisasi semua sistem sebelum permainan dimulai.
 */
void initialize_system() {
    printf("Menginisialisasi sistem...\n");
    load_history_from_file();
    // Inisialisasi pointer global sudah dilakukan di common_types.c
    printf("Sistem berhasil diinisialisasi!\n\n");
}

