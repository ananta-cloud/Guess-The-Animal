#include "utils.h"

void print_separator() {
    printf("==================================================\n");
}

void print_header(const char* title) {
    print_separator();
    printf("          %s\n", title);
    print_separator();
}

/**
 * @brief Menampilkan menu utama kepada pengguna, kini dengan opsi Admin.
 */
void print_main_menu() {
    print_header("ANIMAL GUESSING GAME - MENU UTAMA");
    printf("1. Mulai Permainan\n");
    printf("2. Lihat Riwayat Permainan\n");
    printf("3. Menu Admin\n");
    printf("4. Keluar\n");
    print_separator();
    printf("Pilih menu (1-4): ");
}

/**
 * @brief Menampilkan menu admin.
 */
void print_admin_menu() {
    print_header("MENU ADMIN");
    printf("1. Undo Operasi Terakhir\n");
    printf("2. Kembali ke Menu Utama\n");
    print_separator();
    printf("Pilih opsi (1-2): ");
}

/**
 * @brief Mendapatkan pilihan menu yang valid dari pengguna.
 * @param max_choice Angka pilihan maksimum yang valid.
 * @return Pilihan pengguna dalam bentuk integer.
 */
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

/**
 * @brief Menampilkan pesan selamat datang saat program pertama kali dijalankan.
 */
void print_welcome() {
    system("clear || cls"); // Membersihkan layar konsol
    print_header("SELAMAT DATANG DI ANIMAL GUESSING GAME!");
    printf("Pikirkan seekor hewan, dan saya akan mencoba menebaknya!\n\n");
}

/**
 * @brief Menampilkan pesan perpisahan sebelum program berakhir.
 */
void print_goodbye() {
    print_header("TERIMA KASIH TELAH BERMAIN!");
}

/**
 * @brief Menjeda program dan menunggu input ENTER dari pengguna.
 */
void ready() {
    printf("\nTekan ENTER untuk melanjutkan...");
    getchar();
}

/**
 * @brief Menanyakan kepada pengguna apakah mereka ingin bermain lagi.
 * @return 1 jika ya, 0 jika tidak.
 */
int play_again() {
    printf("\nApakah Anda ingin bermain lagi? ");
    int answer = get_answer();
    
    if (answer == 1) {
        printf("Asyik! Mari bermain lagi!\n\n");
        return 1;
    }
    return 0;
}
