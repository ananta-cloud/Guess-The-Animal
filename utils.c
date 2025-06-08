#include "utils.h"
#include "linked_list.h"
#include "stack_operations.h"
#include "queue_operations.h"

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

void print_statistics_menu() {
    print_header("MENU STATISTIK");
    printf("1. Statistik Umum Permainan\n");
    printf("2. Riwayat Permainan Lengkap\n");
    printf("3. Peringkat Pemain (Multiplayer)\n");
    printf("4. Kembali ke Menu Utama\n");
    print_separator();
    printf("Pilih opsi (1-4): ");
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
    printf("3. Riwayat Undo\n");
    printf("4. Reset Semua Data\n");
    printf("5. Backup Sistem\n");
    printf("6. Restore Backup\n");
    printf("7. Kembali\n");
    print_separator();
    printf("Pilih opsi (1-7): ");
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

/**
 * @brief Membersihkan semua memori dan menyimpan data sebelum keluar.
 */
void cleanup_system() {
    printf("Membersihkan sistem...\n");
    save_history_to_file();
    clear_game_history();
    if (player_queue != NULL) {
        clear_player_queue(player_queue);
        free(player_queue);
        player_queue = NULL;
    }
    clear_undo_stack();
    printf("Sistem berhasil dibersihkan!\n");
}

/**
 * @brief Meminta konfirmasi ya/tidak dari pengguna untuk tindakan berbahaya.
 * @param action Deskripsi tindakan (misal: "reset semua data").
 * @return 1 jika ya, 0 jika tidak.
 */
int confirm_action(const char* action) {
    printf("PERINGATAN: Apakah Anda yakin ingin %s? (yes/no): ", action);
    return get_answer() == 1;
}

void reset_all_data() {
    if (confirm_action("menghapus SEMUA data permainan")) {
        clear_game_history();
        clear_undo_stack();
        if (player_queue != NULL) clear_player_queue(player_queue);
        
        remove(HISTORY_FILE);
        remove(DEFAULT_DB_FILE);
        remove(BACKUP_DB_FILE);
        
        printf("Semua data berhasil dihapus!\n");
    } else {
        printf("Operasi reset dibatalkan.\n");
    }
}

int create_system_backup() {
    printf("Membuat cadangan sistem...\n");
    if (create_backup() != 0) {
        printf("Gagal membuat cadangan database!\n");
        return 0;
    }
    save_history_to_file();
    printf("Cadangan sistem berhasil dibuat!\n");
    return 1;
}

int restore_system_backup() {
    if (!confirm_action("mengganti data saat ini dengan data dari cadangan")) {
        printf("Operasi pemulihan dibatalkan.\n");
        return 0;
    }

    FILE* backup_file = fopen(BACKUP_DB_FILE, "rb");
    if (backup_file == NULL) {
        printf("File cadangan tidak ditemukan!\n");
        return 0;
    }
    fclose(backup_file);

    // Salin file backup ke file utama
    FILE* source = fopen(BACKUP_DB_FILE, "rb");
    FILE* dest = fopen(DEFAULT_DB_FILE, "wb");
    if (source == NULL || dest == NULL) { /* handle error */ return 0; }
    
    char buffer[1024];
    size_t bytes;
    while ((bytes = fread(buffer, 1, sizeof(buffer), source)) > 0) {
        fwrite(buffer, 1, bytes, dest);
    }
    fclose(source);
    fclose(dest);
    
    printf("Sistem berhasil dipulihkan dari cadangan!\n");
    printf("Harap muat ulang data dari menu atau restart aplikasi.\n");
    return 1;
}