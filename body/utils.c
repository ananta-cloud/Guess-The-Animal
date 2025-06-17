#include "../header/tree_operations.h"
#include "../header/linked_list.h"
#include "../header/stack_operations.h"
#include "../header/queue_operations.h"
#include "../header/utils.h"

#ifdef _WIN32
#include <windows.h>
#else
#include <sys/ioctl.h>
#include <unistd.h>
#endif

// --- Text Centering Utility Functions ---

int get_terminal_width()
{
#ifdef _WIN32
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    return csbi.srWindow.Right - csbi.srWindow.Left + 1;
#else
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    return w.ws_col;
#endif
}

// Membersihkan layar
void clear_screen()
{
    system("cls || clear");
}

void ready()
{
    printf("\n");
    prompt_centered("Tekan ENTER untuk melanjutkan...");
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
    {
    }
    getchar();
    clear_screen();
}

// Justify center text
void print_centered(const char *text)
{
    int width = get_terminal_width();
    int len = strlen(text);
    if (len >= width)
    {
        printf("%s\n", text); // Jika teks lebih panjang dari lebar, cetak saja
        return;
    }
    int padding = (width - len) / 2;
    for (int i = 0; i < padding; ++i)
    {
        printf(" ");
    }
    printf("%s\n", text);
}

// Justify center text tanpa baris baru
void prompt_centered(const char *text)
{
    int width = get_terminal_width();
    int len = strlen(text);
    int padding = (width - len) / 2;
    for (int i = 0; i < padding; ++i)
    {
        printf(" ");
    }
    printf("%s", text);
}

// Mencetak header
void print_header(const char *title)
{
    print_centered("=============================================================================================");
    print_centered(title);
    print_centered("=============================================================================================");
    printf("\n");
}

// Untuk patokan input
void print_aligned_prompt(const char* prompt)
{
    // Gunakan string pemisah header sebagai referensi untuk lebar
    const char* border_reference = "=============================================================================================";
    int terminal_width = get_terminal_width();
    int reference_len = strlen(border_reference);

    // Hitung padding yang sama persis seperti yang digunakan oleh header
    int padding = 0;
    if (terminal_width > reference_len) {
        padding = (terminal_width - reference_len) / 2;
    }

    // Cetak spasi untuk padding
    for (int i = 0; i < padding; i++) {
        printf(" ");
    }

    // Cetak teks prompt yang sebenarnya tanpa baris baru
    printf("%s", prompt);
}

// Mencetak garis ke layar
void print_separator()
{
    printf("\n");
    print_centered("--------------------------------------------------------------------------------------------");
}

// Tampilan main menu
void print_main_menu(int highlighted_option)
{
    clear_screen();
    print_header("ANIMAL GUESSING GAME - MENU UTAMA");

    const char *menu_items[] = {
        "[1]. Mulai Permainan Single Player",
        "[2]. Mulai Permainan Multiplayer",
        "[3]. Lihat Statistik",
        "[4]. Menu Admin",
        "[5]. Bantuan",
        "[6]. Keluar"};
    int num_items = sizeof(menu_items) / sizeof(menu_items[0]);
    int max_len = 0;

    for (int i = 0; i < num_items; i++)
    {
        int current_len = strlen(menu_items[i]);
        if (current_len > max_len)
        {
            max_len = current_len;
        }
    }

    int terminal_width = get_terminal_width();
    int padding = (terminal_width > max_len) ? (terminal_width - max_len) / 2 : 0;

    for (int i = 0; i < num_items; i++)
    {
        for (int j = 0; j < padding; j++)
        {
            printf(" ");
        }
        // Logika untuk menyorot opsi yang dipilih
        if ((i + 1) == highlighted_option)
        {
            // Cetak dengan latar belakang berbeda (contoh: teks putih di atas latar belakang biru)
            printf("\x1b[44m\x1b[37m >> %s \x1b[0m\n", menu_items[i]);
        }
        else
        {
            printf("    %s\n", menu_items[i]); // Beri spasi agar rata dengan '>>'
        }
    }

    print_separator();
    // Prompt tidak lagi diperlukan di sini karena tidak ada pengetikan
}

void print_game_menu(int highlighted_option)
{
    clear_screen();
    print_header("MENU PERMAINAN");

    const char *menu_items[] = {
        "[1]. Main Sekali",
        "[2]. Main Terus-menerus",
        "[3]. Lihat Semua Hewan",
        "[4]. Statistik Game",
        "[5]. Kembali ke Menu Utama"};
    int num_items = sizeof(menu_items) / sizeof(menu_items[0]);
    int max_len = 0;

    // Cari panjang string terpanjang
    for (int i = 0; i < num_items; i++)
    {
        int current_len = strlen(menu_items[i]);
        if (current_len > max_len)
        {
            max_len = current_len;
        }
    }

    // Hitung padding untuk blok
    int terminal_width = get_terminal_width();
    int padding = (terminal_width > max_len) ? (terminal_width - max_len) / 2 : 0;

    // Cetak setiap item dengan logika sorotan
    for (int i = 0; i < num_items; i++)
    {
        for (int j = 0; j < padding; j++)
        {
            printf(" ");
        }

        if ((i + 1) == highlighted_option)
        {
            // Opsi yang disorot dengan warna
            printf("\x1b[44m\x1b[37m >> %s \x1b[0m\n", menu_items[i]);
        }
        else
        {
            // Opsi normal dengan spasi agar rata
            printf("    %s\n", menu_items[i]);
        }
    }

    print_separator();
    // Prompt input tidak lagi diperlukan
}

// Ganti fungsi print_statistics_menu Anda dengan yang ini
void print_statistics_menu(int highlighted_option)
{
    clear_screen();
    print_header("MENU STATISTIK");

    const char *menu_items[] = {
        "[1]. Statistik Umum",
        "[2]. Riwayat Permainan",
        "[3]. Ranking Player",
        "[4]. Saran Pertanyaan",
        "[5]. Analisis Pembelajaran",
        "[6]. Kembali"};
    int num_items = sizeof(menu_items) / sizeof(menu_items[0]);
    int max_len = 0;

    for (int i = 0; i < num_items; i++)
    {
        int current_len = strlen(menu_items[i]);
        if (current_len > max_len)
        {
            max_len = current_len;
        }
    }

    int terminal_width = get_terminal_width();
    int padding = (terminal_width > max_len) ? (terminal_width - max_len) / 2 : 0;

    for (int i = 0; i < num_items; i++)
    {
        for (int j = 0; j < padding; j++)
        {
            printf(" ");
        }

        if ((i + 1) == highlighted_option)
        {
            printf("\x1b[44m\x1b[37m >> %s \x1b[0m\n", menu_items[i]);
        }
        else
        {
            printf("    %s\n", menu_items[i]);
        }
    }

    print_separator();
}

// Ganti fungsi print_admin_menu Anda dengan yang ini
void print_admin_menu(int highlighted_option)
{
    clear_screen();
    print_header("MENU ADMIN");

    const char *menu_items[] = {
        "[1]. Lihat Struktur Tree",
        "[2]. Undo Operasi Terakhir",
        "[3]. Riwayat Undo",
        "[4]. Reset Semua Data",
        "[5]. Backup System",
        "[6]. Restore Backup",
        "[7]. Kembali"};
    int num_items = sizeof(menu_items) / sizeof(menu_items[0]);
    int max_len = 0;

    for (int i = 0; i < num_items; i++)
    {
        int current_len = strlen(menu_items[i]);
        if (current_len > max_len)
        {
            max_len = current_len;
        }
    }

    int terminal_width = get_terminal_width();
    int padding = (terminal_width > max_len) ? (terminal_width - max_len) / 2 : 0;

    for (int i = 0; i < num_items; i++)
    {
        for (int j = 0; j < padding; j++)
        {
            printf(" ");
        }

        if ((i + 1) == highlighted_option)
        {
            printf("\x1b[44m\x1b[37m >> %s \x1b[0m\n", menu_items[i]);
        }
        else
        {
            printf("    %s\n", menu_items[i]);
        }
    }

    print_separator();
}

// Untuk mendapat pilihan menu
int get_menu_selection(int max_choice, void (*print_menu_func)(int))
{
    int current_option = 1;
    int key_pressed = 0;

    #ifdef _WIN32
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(hConsole, &cursorInfo);
    cursorInfo.bVisible = FALSE;
    SetConsoleCursorInfo(hConsole, &cursorInfo);
    #endif

    // Hapus layar HANYA SEKALI sebelum loop dimulai
    clear_screen(); 

    while (1)
    {
        // --- PERUBAHAN UTAMA DI SINI ---
        // Alih-alih membersihkan layar, kita pindahkan kursor ke pojok kiri atas.
        // Ini adalah ANSI escape code untuk "Cursor Home".
        printf("\x1b[H"); 
        
        // Panggil fungsi menu yang sesuai untuk menggambar ulang (menimpa) layar
        print_menu_func(current_option);

        // ... sisa kode (bagian _getch(), switch case, dll.) tetap sama ...
        key_pressed = _getch();

        if (key_pressed == 224) { // Tombol Panah
            key_pressed = _getch();
            switch (key_pressed) {
                case 72: current_option--; break; // Atas
                case 80: current_option++; break; // Bawah
            }
        } else { // Tombol WASD dan Enter
            switch (key_pressed) {
                case 'w': case 'W': current_option--; break;
                case 's': case 'S': current_option++; break;
                case 13: // Enter
                    #ifdef _WIN32
                    cursorInfo.bVisible = TRUE;
                    SetConsoleCursorInfo(hConsole, &cursorInfo);
                    #endif
                    // Pastikan layar bersih setelah menu selesai
                    clear_screen(); 
                    return current_option;
            }
        }
        
        if (current_option > max_choice) current_option = 1;
        if (current_option < 1) current_option = max_choice;
    }
}

void print_welcome()
{
    clear_screen();
    print_separator();
    print_centered("SELAMAT DATANG DI ANIMAL GUESSING GAME! 🎉");
    print_separator();
    print_centered("");
    print_centered("Pikirkan seekor hewan, dan saya akan mencoba menebaknya!");
    print_centered("Saya akan belajar dari setiap permainan untuk menjadi lebih pintar.");
    print_centered("Siap untuk tantangan? Mari kita mulai!");
    printf("\n");
}

void print_goodbye()
{
    print_header("TERIMA KASIH TELAH BERMAIN!");
    print_centered("Semoga Anda menikmati permainannya!");
    print_centered("Sampai jumpa lagi!");
}

int play_again()
{
    prompt_centered("\nApakah Anda ingin bermain lagi? (y/n) ");
    int answer = get_answer();
    if (answer == 1)
    {
        print_centered("Asyik! Mari bermain lagi!");
        printf("\n");
        return 1;
    }
    else if (answer == 0)
    {
        print_centered("Terima kasih telah bermain!");
        return 0;
    }
    else
    {
        print_centered("Saya anggap itu sebagai 'tidak'. Terima kasih!");
        return 0;
    }
}

void display_game_rules()
{
    clear_screen();
    print_header("ATURAN PERMAINAN");
    print_centered("1. Pikirkan seekor hewan apa saja");
    print_centered("2. Jawab pertanyaan saya dengan 'yes' atau 'no'");
    print_centered("3. Saya akan mencoba menebak hewan Anda");
    print_centered("4. Jika saya salah, bantu saya belajar dengan memberikan:");
    print_centered("   - Nama hewan yang Anda pikirkan");
    print_centered("   - Pertanyaan yang membedakannya");
    print_centered("5. Dapatkan poin untuk setiap permainan:");
    print_centered("   - 10 poin jika saya menebak benar");
    print_centered("   - 2 poin untuk partisipasi");
    printf("\n");
    print_centered("Tips: Gunakan jawaban yang konsisten untuk hasil terbaik!");
    printf("\n");
}

void initialize_system()
{
    // printf("Menginisialisasi sistem...\n");

    // Load game history
    load_history_from_file();

    // Initialize global variables
    if (player_queue == NULL)
    {
        player_queue = NULL;
    }

    if (undo_stack_top == NULL)
    {
        undo_stack_top = NULL;
    }

    print_centered("Sistem berhasil diinisialisasi!\n");
}

void cleanup_system()
{
    printf("Membersihkan sistem...\n");

    // Save current state
    save_history_to_file();

    // Clear memory
    clear_game_history();

    if (player_queue != NULL)
    {
        clear_player_queue(player_queue);
        free(player_queue);
        player_queue = NULL;
    }

    clear_undo_stack();
    clear_suggestions();

    printf("Sistem berhasil dibersihkan!\n");
}

void reset_all_data()
{
    // 1. Tampilkan header dan peringatan dengan perataan yang benar.
    clear_screen();
    print_header("RESET SEMUA DATA");

    print_aligned_prompt("PERINGATAN: Operasi ini akan menghapus SEMUA data!");
    printf("\n");
    print_aligned_prompt("Tindakan ini tidak dapat diurungkan.");
    printf("\n\n");

    // 2. Minta konfirmasi kepada pengguna HANYA SATU KALI.
    print_aligned_prompt("Apakah Anda benar-benar yakin ingin melanjutkan? (y/n) ");

    if (get_answer() == 1)
    {
        // 3. Jika ya, lakukan proses reset.
        clear_game_history();
        clear_undo_stack();
        clear_suggestions();

        if (player_queue != NULL) {
            clear_player_queue(player_queue);
        }

        remove(HISTORY_FILE);
        remove(DEFAULT_DB_FILE);
        remove(BACKUP_DB_FILE);

        // 4. Beri pesan konfirmasi keberhasilan yang rapi.
        printf("\n");
        print_aligned_prompt("Semua data berhasil dihapus.");
        printf("\n");
    }
    else
    {
        printf("\n");
        print_aligned_prompt("Operasi reset dibatalkan.");
        printf("\n");
    }
}

int create_system_backup()
{
    printf("Membuat backup sistem...\n");

    // Create backup of main database
    if (create_backup() != 0)
    {
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

int restore_system_backup()
{
    printf("Mengembalikan dari backup...\n");

    FILE *backup = fopen(BACKUP_DB_FILE, "r");
    if (backup == NULL)
    {
        printf("File backup tidak ditemukan!\n");
        return 0;
    }
    fclose(backup);

    printf("Operasi ini akan mengganti database saat ini. Lanjutkan? ");
    if (get_answer() != 1)
    {
        printf("Operasi restore dibatalkan.\n");
        return 0;
    }

    // Copy backup to main database
    FILE *source = fopen(BACKUP_DB_FILE, "r");
    FILE *dest = fopen(DEFAULT_DB_FILE, "w");

    if (source == NULL || dest == NULL)
    {
        if (source)
            fclose(source);
        if (dest)
            fclose(dest);
        printf("Gagal mengakses file!\n");
        return 0;
    }

    char buffer[1024];
    size_t bytes;
    while ((bytes = fread(buffer, 1, sizeof(buffer), source)) > 0)
    {
        fwrite(buffer, 1, bytes, dest);
    }

    fclose(source);
    fclose(dest);

    printf("Sistem berhasil dikembalikan dari backup!\n");
    return 1;
}

int get_valid_integer(int min, int max)
{
    char input[20];
    int value;

    while (1)
    {
        if (fgets(input, sizeof(input), stdin) != NULL)
        {
            value = atoi(input);
            if (value >= min && value <= max)
            {
                return value;
            }
        }
        printf("Masukkan angka antara %d-%d: ", min, max);
    }
}

void get_valid_string(char *buffer, int max_length, const char *prompt)
{
    char temp[256];

    while (1)
    {
        printf("%s", prompt);
        if (fgets(temp, sizeof(temp), stdin) != NULL)
        {
            trim_string(temp);
            if (strlen(temp) > 0 && strlen(temp) < max_length)
            {
                strcpy(buffer, temp);
                return;
            }
        }
        printf("Input tidak valid! Coba lagi.\n");
    }
}

int confirm_action(const char *action)
{
    printf("Apakah Anda yakin ingin %s? ", action);
    return get_answer();
}

void display_comprehensive_statistics()
{
    clear_screen();
    print_header("STATISTIK KOMPREHENSIF");

    // --- Logika Perataan Utama ---
    // Hitung padding utama satu kali untuk seluruh blok konten
    const char* border_reference = "=============================================================================================";
    int terminal_width = get_terminal_width();
    int reference_len = strlen(border_reference);
    int padding = (terminal_width > reference_len) ? (terminal_width - reference_len) / 2 : 0;
    
    // --- Bagian 1: Statistik Permainan ---
    printf("\n");
    for (int i = 0; i < padding; i++) { printf(" "); }
    printf("Statistik Permainan\n");
    for (int i = 0; i < padding; i++) { printf(" "); }
    printf("--------------------------------------------------------------------------------------------\n");

    const int game_label_width = 22; // Lebar untuk perataan titik dua
    for (int i = 0; i < padding; i++) { printf(" "); }
    printf("%-*s: %d\n", game_label_width, "Total Permainan", get_total_games());
    
    for (int i = 0; i < padding; i++) { printf(" "); }
    printf("%-*s: %d\n", game_label_width, "Tebakan Benar", get_correct_guesses());

    for (int i = 0; i < padding; i++) { printf(" "); }
    printf("%-*s: %d\n", game_label_width, "Tebakan Salah", get_total_games() - get_correct_guesses());

    for (int i = 0; i < padding; i++) { printf(" "); }
    printf("%-*s: %.1f%%\n", game_label_width, "Tingkat Keberhasilan", get_success_rate());

    // --- Bagian 2: Statistik Player ---
    if (get_total_players() > 0) {
        printf("\n");
        for (int i = 0; i < padding; i++) { printf(" "); }
        printf("Statistik Player\n");
        for (int i = 0; i < padding; i++) { printf(" "); }
        printf("--------------------------------------------------------------------------------------------\n");

        const int player_label_width = 15;
        for (int i = 0; i < padding; i++) { printf(" "); }
        printf("%-*s: %d\n", player_label_width, "Total Player", get_total_players());

        Player* best = find_best_player();
        if (best != NULL) {
            char best_player_str[100];
            sprintf(best_player_str, "%s (Skor: %d)", best->name, best->score);
            for (int i = 0; i < padding; i++) { printf(" "); }
            printf("%-*s: %s\n", player_label_width, "Player Terbaik", best_player_str);
        }
    }

    // --- Bagian 3: Statistik Sistem ---
    printf("\n");
    for (int i = 0; i < padding; i++) { printf(" "); }
    printf("Statistik Sistem\n");
    for (int i = 0; i < padding; i++) { printf(" "); }
    printf("--------------------------------------------------------------------------------------------\n");
    
    const int sys_label_width = 22;
    for (int i = 0; i < padding; i++) { printf(" "); }
    printf("%-*s: %d\n", sys_label_width, "Operasi Undo Tersedia", get_undo_stack_size());

    for (int i = 0; i < padding; i++) { printf(" "); }
    // Asumsi 'suggestion_list' adalah variabel global yang bisa diakses
    printf("%-*s: %s\n", sys_label_width, "Saran Pertanyaan", suggestion_list ? "Ada" : "Belum ada");
    
    printf("\n");
}

void display_learning_analytics()
{
    clear_screen();
    print_header("ANALISIS PEMBELAJARAN");

    const char* border_reference = "=============================================================================================";
    int terminal_width = get_terminal_width();
    int reference_len = strlen(border_reference);
    int padding = (terminal_width > reference_len) ? (terminal_width - reference_len) / 2 : 0;

    // --- Bagian 1: Kemajuan Pembelajaran ---
    printf("\n");
    for (int i = 0; i < padding; i++) { printf(" "); }
    printf("KEMAJUAN PEMBELAJARAN\n");
    for (int i = 0; i < padding; i++) { printf(" "); }
    printf("--------------------------------------------------------------------------------------------\n");

    const int label_width = 20;
    double success_rate = get_success_rate();
    char* learning_level;

    if (success_rate >= 80) learning_level = "Sangat Baik";
    else if (success_rate >= 60) learning_level = "Baik";
    else if (success_rate >= 40) learning_level = "Cukup";
    else learning_level = "Perlu Ditingkatkan";

    char rate_str[50];
    sprintf(rate_str, "%s (%.1f%%)", learning_level, success_rate);

    for (int i = 0; i < padding; i++) { printf(" "); }
    printf("%-*s: %s\n", label_width, "Tingkat Pembelajaran", rate_str);

    for (int i = 0; i < padding; i++) { printf(" "); }
    printf("%-*s: %d permainan\n", label_width, "Total Pembelajaran", get_total_games());

    // --- Bagian 2: Rekomendasi ---
    printf("\n");
    for (int i = 0; i < padding; i++) { printf(" "); }
    printf("REKOMENDASI\n");
    for (int i = 0; i < padding; i++) { printf(" "); }
    printf("--------------------------------------------------------------------------------------------\n");

    if (success_rate < 50) {
        for (int i = 0; i < padding; i++) { printf(" "); }
        printf("- Mainkan lebih banyak untuk meningkatkan akurasi.\n");
        for (int i = 0; i < padding; i++) { printf(" "); }
        printf("- Berikan pertanyaan yang lebih spesifik saat belajar.\n");
    } else {
        for (int i = 0; i < padding; i++) { printf(" "); }
        printf("- Sistem sudah belajar dengan baik!\n");
        for (int i = 0; i < padding; i++) { printf(" "); }
        printf("- Terus mainkan untuk menambah variasi hewan.\n");
    }
    printf("\n");
}

void display_system_status()
{
    print_header("STATUS SISTEM");

    printf("FILE SISTEM:\n");

    FILE *db = fopen(DEFAULT_DB_FILE, "r");
    printf("   Database: %s\n", db ? "Ada" : "Tidak ada");
    if (db)
        fclose(db);

    FILE *backup = fopen(BACKUP_DB_FILE, "r");
    printf("   Backup: %s\n", backup ? "Ada" : "Tidak ada");
    if (backup)
        fclose(backup);

    FILE *history = fopen(HISTORY_FILE, "r");
    printf("   History: %s\n", history ? "Ada" : "Tidak ada");
    if (history)
        fclose(history);

    printf("\nMEMORI:\n");
    printf("   Game History: %d entri\n", get_total_games());
    printf("   Undo Stack: %d operasi\n", get_undo_stack_size());
    printf("   Player Queue: %d player\n", get_total_players());

    printf("\nPERFORMA:\n");
    printf("   Success Rate: %.1f%%\n", get_success_rate());
    printf("   Status: %s\n", "Normal");
    printf("\n");
}

void show_help_information()
{
    print_header("BANTUAN & INFORMASI");

    print_centered("CARA BERMAIN:\n");
    print_centered("   1. Pilih mode Single Player atau Multiplayer");
    print_centered("   2. Pikirkan seekor hewan");
    print_centered("   3. Jawab pertanyaan dengan 'yes/y/ya' atau 'no/n/tidak'");
    print_centered("   4. Biarkan saya menebak hewan Anda!");
    print_centered("   5. Jika salah, bantu saya belajar\n");

    print_centered("PERINTAH YANG DITERIMA:");
    print_centered("   Jawaban: yes, y, ya, iya (untuk Ya)");
    print_centered("   Jawaban: no, n, tidak, nggak (untuk Tidak)\n");

    print_centered("FITUR LANJUTAN:");
    print_centered("   Undo: Batalkan pembelajaran terakhir");
    print_centered("   Statistik: Lihat performa dan progress");
    print_centered("   Multiplayer: Bermain dengan teman");
    print_centered("   Backup: Simpan dan pulihkan data\n");

    print_centered("TROUBLESHOOTING:");
    print_centered("   - Jika game lambat: Reset data di menu admin");
    print_centered("   - Jika error: Coba restore backup");
    print_centered("   - Jika data hilang: Periksa file database\n");

    print_centered("VERSI & INFO:");
    print_centered("   Animal Guessing Game v2.0");
    print_centered("   Menggunakan Binary Tree & Data Structures");
    print_centered("   Mendukung pembelajaran adaptif\n");
}

char *format_timestamp(time_t timestamp)
{
    static char buffer[50];
    strftime(buffer, sizeof(buffer), "%d/%m/%Y %H:%M:%S", localtime(&timestamp));
    return buffer;
}

int get_days_since_last_play()
{
    if (game_history_head == NULL)
        return -1;

    time_t now = time(NULL);
    time_t last_play = game_history_head->timestamp;

    double diff = difftime(now, last_play);
    return (int)(diff / (24 * 60 * 60)); // Convert seconds to days
}

void display_session_summary()
{
    clear_screen();
    print_header("RINGKASAN SESI");

    int days_since = get_days_since_last_play();
    char buffer[128];

    if (days_since >= 0)
    {
        if (days_since == 0)
        {
            sprintf(buffer, "Anda bermain hari ini!");
        }
        else if (days_since == 1)
        {
            sprintf(buffer, "Terakhir bermain: Kemarin");
        }
        else
        {
            sprintf(buffer, "Terakhir bermain: %d hari lalu", days_since);
        }
        print_centered(buffer);
    }
    sprintf(buffer, "Total permainan: %d", get_total_games());
    print_centered(buffer);

    sprintf(buffer, "Tingkat keberhasilan: %.1f%%", get_success_rate());
    print_centered(buffer);

    if (get_total_players() > 0)
    {
        sprintf(buffer, "Player aktif: %d", get_total_players());
        print_centered(buffer);
    }
    printf("\n");
    print_centered("Terima kasih telah bermain!");
    print_centered("Data otomatis tersimpan.");
    printf("\n");
}