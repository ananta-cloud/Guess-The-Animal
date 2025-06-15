#include "../header.h"

void print_main_menu() {
    print_header("ANIMAL GUESSING GAME - MENU UTAMA");
    printf("1. Mulai Permainan Single Player\n");
    printf("2. Mulai Permainan Multiplayer\n");
    printf("3. Lihat Statistik\n");
    printf("4. Menu Admin\n");
    printf("5. Bantuan\n");
    printf("6. Keluar\n");
    print_separator();
    printf("Pilih menu (1-6): ");
}

void print_game_menu() {
    print_header("MENU PERMAINAN");
    printf("1. Main Sekali\n");
    printf("2. Main Terus-menerus\n");
    printf("3. Lihat Semua Hewan\n");
    printf("4. Statistik Game\n");
    printf("5. Kembali ke Menu Utama\n");
    print_separator();
    printf("Pilih opsi (1-5): ");
}

void print_statistics_menu() {
    print_header("MENU STATISTIK");
    printf("1. Statistik Umum\n");
    printf("2. Riwayat Permainan\n");
    printf("3. Ranking Player\n");
    printf("4. Saran Pertanyaan\n");
    printf("5. Analisis Pembelajaran\n");
    printf("6. Kembali\n");
    print_separator();
    printf("Pilih opsi (1-6): ");
}

void print_admin_menu() {
    print_header("MENU ADMIN");
    printf("1. Lihat Struktur Tree\n");
    printf("2. Undo Operasi Terakhir\n");
    printf("3. Riwayat Undo\n");
    printf("4. Reset Semua Data\n");
    printf("5. Backup System\n");
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
    system("clear || cls"); // Clear screen for both Unix and Windows
    print_separator();
    printf("SELAMAT DATANG DI ANIMAL GUESSING GAME! 🎉\n");
    print_separator();
    printf("Pikirkan seekor hewan, dan saya akan mencoba menebaknya!\n");
    printf("Saya akan belajar dari setiap permainan untuk menjadi lebih pintar.\n");
    printf("Siap untuk tantangan? Mari kita mulai!\n\n");
}

void print_goodbye() {
    print_header("TERIMA KASIH TELAH BERMAIN!");
    printf("Semoga Anda menikmati permainannya!\n");
    printf("Sampai jumpa lagi!\n");
    print_separator();
}

void ready() {
    printf("\nTekan ENTER untuk melanjutkan...");
    getchar();
    printf("\nMari kita mulai!\n\n");
}

int play_again() {
    printf("\nApakah Anda ingin bermain lagi? ");
    int answer = get_answer();
    
    if (answer == 1) {
        printf("Asyik! Mari bermain lagi!\n\n");
        return 1;
    } else if (answer == 0) {
        printf("Terima kasih telah bermain!\n");
        return 0;
    } else {
        printf("Saya anggap itu sebagai 'tidak'. Terima kasih!\n");
        return 0;
    }
}

void display_game_rules() {
    print_header("ATURAN PERMAINAN");
    printf("1. Pikirkan seekor hewan apa saja\n");
    printf("2. Jawab pertanyaan saya dengan 'yes' atau 'no'\n");
    printf("3. Saya akan mencoba menebak hewan Anda\n");
    printf("4. Jika saya salah, bantu saya belajar dengan memberikan:\n");
    printf("   - Nama hewan yang Anda pikirkan\n");
    printf("   - Pertanyaan yang membedakannya\n");
    printf("5. Dapatkan poin untuk setiap permainan:\n");
    printf("   - 10 poin jika saya menebak benar\n");
    printf("   - 2 poin untuk partisipasi\n\n");
    printf("Tips: Gunakan jawaban yang konsisten untuk hasil terbaik!\n\n");
}

void initialize_system() {
    printf("Menginisialisasi sistem...\n");
    
    // Load game history
    load_history_from_file();
    
    // Initialize global variables
    if (player_queue == NULL) {
        player_queue = NULL;
    }
    
    if (undo_stack_top == NULL) {
        undo_stack_top = NULL;
    }
    
    printf("Sistem berhasil diinisialisasi!\n\n");
}

void cleanup_system() {
    printf("Membersihkan sistem...\n");
    
    // Save current state
    save_history_to_file();
    
    // Clear memory
    clear_game_history();
    
    if (player_queue != NULL) {
        clear_player_queue(player_queue);
        free(player_queue);
        player_queue = NULL;
    }
    
    clear_undo_stack();
    clear_suggestions();
    
    printf("Sistem berhasil dibersihkan!\n");
}

void reset_all_data() {
    printf("PERINGATAN: Operasi ini akan menghapus SEMUA data!\n");
    printf("Apakah Anda yakin ingin melanjutkan? ");
    
    if (get_answer() == 1) {
        // Clear all data structures
        clear_game_history();
        clear_undo_stack();
        clear_suggestions();
        
        if (player_queue != NULL) {
            clear_player_queue(player_queue);
        }
        
        // Remove files
        remove(HISTORY_FILE);
        remove(DEFAULT_DB_FILE);
        remove(BACKUP_DB_FILE);
        
        printf("Semua data berhasil dihapus!\n");
        printf("Sistem akan membuat database baru saat permainan dimulai.\n");
    } else {
        printf("Operasi reset dibatalkan.\n");
    }
}

int create_system_backup() {
    printf("Membuat backup sistem...\n");
    
    // Create backup of main database
    if (create_backup() != 0) {
        printf("Gagal membuat backup database!\n");
        return 0;
    }
    
    // Save current history
    save_history_to_file();
    
    // Create timestamp for backup info
    time_t now = time(NULL);
    char timestamp[50];
    strftime(timestamp, sizeof(timestamp), "%Y%m%d_%H%M%S", localtime(&now));
    
    printf("Backup sistem berhasil dibuat!\n");
    printf("Timestamp: %s\n", timestamp);
    
    return 1;
}

int restore_system_backup() {
    printf("Mengembalikan dari backup...\n");
    
    FILE* backup = fopen(BACKUP_DB_FILE, "r");
    if (backup == NULL) {
        printf("File backup tidak ditemukan!\n");
        return 0;
    }
    fclose(backup);
    
    printf("Operasi ini akan mengganti database saat ini. Lanjutkan? ");
    if (get_answer() != 1) {
        printf("Operasi restore dibatalkan.\n");
        return 0;
    }
    
    // Copy backup to main database
    FILE* source = fopen(BACKUP_DB_FILE, "r");
    FILE* dest = fopen(DEFAULT_DB_FILE, "w");
    
    if (source == NULL || dest == NULL) {
        if (source) fclose(source);
        if (dest) fclose(dest);
        printf("Gagal mengakses file!\n");
        return 0;
    }
    
    char buffer[1024];
    size_t bytes;
    while ((bytes = fread(buffer, 1, sizeof(buffer), source)) > 0) {
        fwrite(buffer, 1, bytes, dest);
    }
    
    fclose(source);
    fclose(dest);
    
    printf("Sistem berhasil dikembalikan dari backup!\n");
    return 1;
}

int get_valid_integer(int min, int max) {
    char input[20];
    int value;
    
    while (1) {
        if (fgets(input, sizeof(input), stdin) != NULL) {
            value = atoi(input);
            if (value >= min && value <= max) {
                return value;
            }
        }
        printf("Masukkan angka antara %d-%d: ", min, max);
    }
}

void get_valid_string(char* buffer, int max_length, const char* prompt) {
    char temp[256];
    
    while (1) {
        printf("%s", prompt);
        if (fgets(temp, sizeof(temp), stdin) != NULL) {
            trim_string(temp);
            if (strlen(temp) > 0 && strlen(temp) < max_length) {
                strcpy(buffer, temp);
                return;
            }
        }
        printf("Input tidak valid! Coba lagi.\n");
    }
}

int confirm_action(const char* action) {
    printf("Apakah Anda yakin ingin %s? ", action);
    return get_answer();
}

void display_comprehensive_statistics() {
    print_header("STATISTIK KOMPREHENSIF");
    
    // Game statistics
    display_game_statistics();
    
    // Player statistics if available
    if (get_total_players() > 0) {
        printf("STATISTIK PLAYER:\n");
        printf("   Total Player: %d\n", get_total_players());
        
        Player* best = find_best_player();
        if (best != NULL) {
            printf("   Player Terbaik: %s (Skor: %d)\n", best->name, best->score);
        }
        printf("\n");
    }
    
    // System statistics
    printf("STATISTIK SISTEM:\n");
    printf("   Operasi Undo Tersedia: %d\n", get_undo_stack_size());
    printf("   Saran Pertanyaan: %s\n", suggestion_list ? "Ada" : "Belum ada");
    printf("\n");
}

void display_learning_analytics() {
    print_header("ANALISIS PEMBELAJARAN");
    
    printf("KEMAJUAN PEMBELAJARAN:\n");
    int total_games = get_total_games();
    double success_rate = get_success_rate();
    
    printf("   Tingkat Pembelajaran: ");
    if (success_rate >= 80) printf("Sangat Baik (%.1f%%)\n", success_rate);
    else if (success_rate >= 60) printf("Baik (%.1f%%)\n", success_rate);
    else if (success_rate >= 40) printf("Sedang (%.1f%%)\n", success_rate);
    else printf("Perlu Ditingkatkan (%.1f%%)\n", success_rate);
    
    printf("   Total Pembelajaran: %d permainan\n", total_games);
    
    if (total_games > 0) {
        int recent_performance = 0; // Could be calculated from recent games
        printf("   Performa Terbaru: %s\n", 
               recent_performance > 0 ? "Membaik" : "Stabil");
    }
    
    printf("\nREKOMENDASI:\n");
    if (success_rate < 50) {
        printf("   - Mainkan lebih banyak untuk meningkatkan akurasi\n");
        printf("   - Berikan pertanyaan yang lebih spesifik saat pembelajaran\n");
    } else {
        printf("   - Sistem sudah belajar dengan baik!\n");
        printf("   - Terus mainkan untuk variasi hewan yang lebih banyak\n");
    }
    printf("\n");
}

void display_system_status() {
    print_header("STATUS SISTEM");
    
    printf("FILE SISTEM:\n");
    
    FILE* db = fopen(DEFAULT_DB_FILE, "r");
    printf("   Database: %s\n", db ? "Ada" : "Tidak ada");
    if (db) fclose(db);
    
    FILE* backup = fopen(BACKUP_DB_FILE, "r");
    printf("   Backup: %s\n", backup ? "Ada" : "Tidak ada");
    if (backup) fclose(backup);
    
    FILE* history = fopen(HISTORY_FILE, "r");
    printf("   History: %s\n", history ? "Ada" : "Tidak ada");
    if (history) fclose(history);
    
    printf("\nMEMORI:\n");
    printf("   Game History: %d entri\n", get_total_games());
    printf("   Undo Stack: %d operasi\n", get_undo_stack_size());
    printf("   Player Queue: %d player\n", get_total_players());
    
    printf("\nPERFORMA:\n");
    printf("   Success Rate: %.1f%%\n", get_success_rate());
    printf("   Status: %s\n", "Normal");
    printf("\n");
}

void show_help_information() {
    print_header("BANTUAN & INFORMASI");
    
    printf("CARA BERMAIN:\n");
    printf("   1. Pilih mode Single Player atau Multiplayer\n");
    printf("   2. Pikirkan seekor hewan\n");
    printf("   3. Jawab pertanyaan dengan 'yes/y/ya' atau 'no/n/tidak'\n");
    printf("   4. Biarkan saya menebak hewan Anda!\n");
    printf("   5. Jika salah, bantu saya belajar\n\n");
    
    printf("PERINTAH YANG DITERIMA:\n");
    printf("   Jawaban: yes, y, ya, iya (untuk Ya)\n");
    printf("   Jawaban: no, n, tidak, nggak (untuk Tidak)\n\n");
    
    printf("FITUR LANJUTAN:\n");
    printf("   Undo: Batalkan pembelajaran terakhir\n");
    printf("   Statistik: Lihat performa dan progress\n");
    printf("   Multiplayer: Bermain dengan teman\n");
    printf("   Backup: Simpan dan pulihkan data\n\n");
    
    printf("TROUBLESHOOTING:\n");
    printf("   - Jika game lambat: Reset data di menu admin\n");
    printf("   - Jika error: Coba restore backup\n");
    printf("   - Jika data hilang: Periksa file database\n\n");
    
    printf("VERSI & INFO:\n");
    printf("   Animal Guessing Game v2.0\n");
    printf("   Menggunakan Binary Tree & Data Structures\n");
    printf("   Mendukung pembelajaran adaptif\n\n");
}

char* format_timestamp(time_t timestamp) {
    static char buffer[50];
    strftime(buffer, sizeof(buffer), "%d/%m/%Y %H:%M:%S", localtime(&timestamp));
    return buffer;
}

int get_days_since_last_play() {
    if (game_history_head == NULL) return -1;
    
    time_t now = time(NULL);
    time_t last_play = game_history_head->timestamp;
    
    double diff = difftime(now, last_play);
    return (int)(diff / (24 * 60 * 60)); // Convert seconds to days
}

void display_session_summary() {
    print_header("RINGKASAN SESI");
    
    int days_since = get_days_since_last_play();
    if (days_since >= 0) {
        if (days_since == 0) {
            printf("Anda bermain hari ini!\n");
        } else if (days_since == 1) {
            printf("Terakhir bermain: Kemarin\n");
        } else {
            printf("Terakhir bermain: %d hari lalu\n", days_since);
        }
    }
    
    printf("Total permainan: %d\n", get_total_games());
    printf("Tingkat keberhasilan: %.1f%%\n", get_success_rate());
    
    if (get_total_players() > 0) {
        printf("Player aktif: %d\n", get_total_players());
    }
    
    printf("\nTerima kasih telah bermain!\n");
    printf("Data otomatis tersimpan.\n\n");
}