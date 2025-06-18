#include "../header/linked_list.h"
#include "../header/utils.h"

void add_game_history(int game_number, const char* animal, int was_correct) {
    GameHistory* new_history = (GameHistory*)malloc(sizeof(GameHistory));
    if (new_history == NULL) {
        printf("Error: Tidak cukup memory untuk history!\n");
        return;
    }
    
    new_history->game_number = game_number;
    strncpy(new_history->guessed_animal, animal, MAX_TEXT_LENGTH - 1);
    new_history->guessed_animal[MAX_TEXT_LENGTH - 1] = '\0';
    new_history->was_correct = was_correct;
    new_history->timestamp = time(NULL);
    new_history->next = game_history_head;
    
    game_history_head = new_history;
    
    // Auto-save history
    save_history_to_file();
}

// Di dalam file body/linked_list.c

void display_game_history() {
    clear_screen();
    print_header("Riwayat Permainan");

    if (game_history_head == NULL) {
        print_centered("Belum ada riwayat permainan.");
        return;
    }
    
    // Hitung total node
    int total_nodes = 0;
    GameHistory* current = game_history_head;
    while (current != NULL) {
        total_nodes++;
        current = current->next;
    }

    // Alokasikan array untuk menyimpan pointer ke semua node
    GameHistory** history_array = (GameHistory**)malloc(total_nodes * sizeof(GameHistory*));
    if (history_array == NULL) {
        print_centered("Error: Tidak cukup memory untuk menampilkan riwayat!");
        return;
    }

    // Isi array dengan pointer ke node, dimulai dari terlama ke terbaru
    current = game_history_head;
    for (int i = total_nodes - 1; i >= 0; i--) {
        history_array[i] = current;
        current = current->next;
    }

    // --- PENYESUAIAN LEBAR TABEL AGAR SESUAI HEADER ---
    const char* border_reference = "=============================================================================================";
    const int TOTAL_TABLE_WIDTH = strlen(border_reference);
    const int GAME_COL_WIDTH = 5;
    const int STATUS_COL_WIDTH = 10;
    const int TIME_COL_WIDTH = 20;
    const int TEXT_COL_WIDTH = TOTAL_TABLE_WIDTH - GAME_COL_WIDTH - STATUS_COL_WIDTH - TIME_COL_WIDTH - 3; // -3 untuk spasi

    char separator[TOTAL_TABLE_WIDTH + 1];
    memset(separator, '-', TOTAL_TABLE_WIDTH);
    separator[TOTAL_TABLE_WIDTH] = '\0';

    int terminal_width = get_terminal_width();
    int padding = (terminal_width > TOTAL_TABLE_WIDTH) ? (terminal_width - TOTAL_TABLE_WIDTH) / 2 : 0;

    // --- Cetak Tabel dengan Lebar dan Perataan Baru ---
    for (int i = 0; i < padding; i++) { printf(" "); }
    printf("%-*s %-*s %-*s %-*s\n", 
           GAME_COL_WIDTH, "Game", 
           TEXT_COL_WIDTH, "Hewan/Pertanyaan", 
           STATUS_COL_WIDTH, "Status", 
           TIME_COL_WIDTH, "Waktu");
    
    for (int i = 0; i < padding; i++) { printf(" "); }
    printf("%s\n", separator);
    
    // Tampilkan dari yang paling lama (indeks terakhir) ke yang terbaru (indeks 0)
    for (int i = 0; i < total_nodes; i++) {
        char* status = history_array[i]->was_correct ? "BENAR" : "SALAH";
        char time_str[50];
        strftime(time_str, sizeof(time_str), "%d/%m/%Y %H:%M", localtime(&history_array[i]->timestamp));
        
        char text_to_display[TEXT_COL_WIDTH + 1];
        if (strlen(history_array[i]->guessed_animal) > TEXT_COL_WIDTH) {
            strncpy(text_to_display, history_array[i]->guessed_animal, TEXT_COL_WIDTH - 3);
            text_to_display[TEXT_COL_WIDTH - 3] = '\0';
            strcat(text_to_display, "...");
        } else {
            strcpy(text_to_display, history_array[i]->guessed_animal);
        }

        for (int j = 0; j < padding; j++) { printf(" "); }
        printf("%-*d %-*s %-*s %-*s\n", 
               GAME_COL_WIDTH, history_array[i]->game_number, 
               TEXT_COL_WIDTH, text_to_display,
               STATUS_COL_WIDTH, status, 
               TIME_COL_WIDTH, time_str);
    }
    
    // Bebaskan memori array
    free(history_array);
    printf("\n");
}

void save_history_to_file() {
    FILE* file = fopen(HISTORY_FILE, "w");
    if (file == NULL) return;
    
    GameHistory* current = game_history_head;
    while (current != NULL) {
        fprintf(file, "%d|%s|%d|%lld\n", 
                current->game_number,
                current->guessed_animal,
                current->was_correct,
                current->timestamp);
        current = current->next;
    }
    fclose(file);
}

void load_history_from_file() {
    FILE* file = fopen(HISTORY_FILE, "r");
    if (file == NULL) return;
    
    char line[512];
    while (fgets(line, sizeof(line), file)) {
        trim_string(line);
        
        char* token = strtok(line, "|");
        if (token == NULL) continue;
        int game_num = atoi(token);
        
        token = strtok(NULL, "|");
        if (token == NULL) continue;
        char animal[MAX_TEXT_LENGTH];
        strncpy(animal, token, MAX_TEXT_LENGTH - 1);
        animal[MAX_TEXT_LENGTH - 1] = '\0';
        
        token = strtok(NULL, "|");
        if (token == NULL) continue;
        int was_correct = atoi(token);
        
        token = strtok(NULL, "|");
        if (token == NULL) continue;
        time_t timestamp = (time_t)atol(token);
        
        // Membuat Node Riwayat baru
        GameHistory* new_history = (GameHistory*)malloc(sizeof(GameHistory));
        if (new_history != NULL) {
            new_history->game_number = game_num;
            strcpy(new_history->guessed_animal, animal);
            new_history->was_correct = was_correct;
            new_history->timestamp = timestamp;
            new_history->next = game_history_head;
            game_history_head = new_history;
        }
    }
    
    fclose(file);
}

void clear_game_history() {
    GameHistory* current = game_history_head;
    while (current != NULL) {
        GameHistory* temp = current;
        current = current->next;
        free(temp);
    }
    game_history_head = NULL;
}

int get_total_games() {
    int count = 0;
    GameHistory* current = game_history_head;
    while (current != NULL) {
        count++;
        current = current->next;
    }
    return count;
}

int get_correct_guesses() {
    int count = 0;
    GameHistory* current = game_history_head;
    while (current != NULL) {
        if (current->was_correct) count++;
        current = current->next;
    }
    return count;
}

double get_success_rate() {
    int total = get_total_games();
    if (total == 0) return 0.0;
    
    int correct = get_correct_guesses();
    return ((double)correct / total) * 100.0;
}

void display_game_statistics() {
    print_header("Statistik Permainan");

    const char* border_reference = "=============================================================================================";
    int terminal_width = get_terminal_width();
    int reference_len = strlen(border_reference);
    int padding = (terminal_width > reference_len) ? (terminal_width - reference_len) / 2 : 0;
    
    int total_games = get_total_games();
    int correct_guesses = get_correct_guesses();
    double success_rate = get_success_rate();
    for (int i = 0; i < padding; i++) { printf(" "); }
    printf("Total Permainan      : %d\n", total_games);
    for (int i = 0; i < padding; i++) { printf(" "); }
    printf("Tebakan Benar        : %d\n", correct_guesses);

    // Baris 3
    for (int i = 0; i < padding; i++) { printf(" "); }
    printf("Tebakan Salah        : %d\n", total_games - correct_guesses);

    // Baris 4
    for (int i = 0; i < padding; i++) { printf(" "); }
    printf("Tingkat Keberhasilan : %.1f%%\n", success_rate);

    // Baris 5 (jika ada data permainan)
    if (total_games > 0 && game_history_head != NULL) {
        char time_str[50];
        strftime(time_str, sizeof(time_str), "%d/%m/%Y %H:%M", localtime(&game_history_head->timestamp));
        
        for (int i = 0; i < padding; i++) { printf(" "); }
        printf("Permainan Terakhir   : %s\n", time_str);
    }
    
    printf("\n");
}

void add_question_suggestion(const char* question, int was_successful) {
    QuestionSuggestion* current = suggestion_list;
    
    // Check apakah pertanyaan sudah ada
    while (current != NULL) {
        if (strcmp(current->question, question) == 0) {
            current->usage_count++;
            update_question_success_rate(question, was_successful);
            return;
        }
        current = current->next;
    }
    
    // Membuat saran baru
    QuestionSuggestion* new_suggestion = (QuestionSuggestion*)malloc(sizeof(QuestionSuggestion));
    if (new_suggestion == NULL) return;
    
    strncpy(new_suggestion->question, question, MAX_TEXT_LENGTH - 1);
    new_suggestion->question[MAX_TEXT_LENGTH - 1] = '\0';
    new_suggestion->usage_count = 1;
    new_suggestion->success_rate = was_successful ? 100.0 : 0.0;
    new_suggestion->next = suggestion_list;
    
    suggestion_list = new_suggestion;
}

void update_question_success_rate(const char* question, int was_successful) {
    QuestionSuggestion* current = suggestion_list;
    while (current != NULL) {
        if (strcmp(current->question, question) == 0) {
            double weight = 0.8; 
            current->success_rate = (current->success_rate * weight) + 
                                   ((was_successful ? 100.0 : 0.0) * (1.0 - weight));
            return;
        }
        current = current->next;
    }
}

void display_question_suggestions() {
    if (suggestion_list == NULL) {
        printf("Belum ada saran pertanyaan.\n");
        return;
    }
    
    print_header("Saran Pertanyaan Terbaik");
    printf("%-40s %-8s %-12s\n", "Pertanyaan", "Digunakan", "Tingkat Sukses");
    printf("----------------------------------------------------------------\n");
    
    QuestionSuggestion* current = suggestion_list;
    while (current != NULL) {
        printf("%-40s %-8d %.1f%%\n", 
               current->question, 
               current->usage_count,
               current->success_rate);
        current = current->next;
    }
    printf("\n");
}

char* get_best_question_suggestion() {
    if (suggestion_list == NULL) return NULL;
    
    QuestionSuggestion* best = suggestion_list;
    QuestionSuggestion* current = suggestion_list->next;
    
    while (current != NULL) {
        double best_score = best->success_rate * (best->usage_count > 0 ? 1.0 : 0.5);
        double current_score = current->success_rate * (current->usage_count > 0 ? 1.0 : 0.5);
        
        if (current_score > best_score) {
            best = current;
        }
        current = current->next;
    }
    
    return best->question;
}

void clear_suggestions() {
    QuestionSuggestion* current = suggestion_list;
    while (current != NULL) {
        QuestionSuggestion* temp = current;
        current = current->next;
        free(temp);
    }
    suggestion_list = NULL;
}

GameHistory* find_game_by_number(int game_number) {
    GameHistory* current = game_history_head;
    while (current != NULL) {
        if (current->game_number == game_number) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

void display_recent_games(int count) {
    print_header("Permainan Terbaru");
    
    GameHistory* current = game_history_head;
    int displayed = 0;
    
    printf("%-5s %-25s %-10s\n", "Game", "Hewan", "Status");
    printf("------------------------------------------\n");
    
    while (current != NULL && displayed < count) {
        char* status = current->was_correct ? "BENAR" : "SALAH";
        printf("%-5d %-25s %-10s\n", 
               current->game_number, 
               current->guessed_animal, 
               status);
        
        current = current->next;
        displayed++;
    }
    printf("\n");
}
