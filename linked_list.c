#include "linked_list.h"
#include "utils.h"
#include "common_types.h"

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
}

void display_game_history() {
    if (game_history_head == NULL) {
        printf("Belum ada riwayat permainan.\n");
        return;
    }
    
    print_header("RIWAYAT PERMAINAN");
    printf("%-5s %-25s %-10s %-20s\n", "Game", "Hewan", "Status", "Waktu");
    printf("-------------------------------------------------------------\n");
    
    GameHistory* current = game_history_head;
    while (current != NULL) {
        char* status = current->was_correct ? "BENAR" : "SALAH";
        char time_str[50];
        strftime(time_str, sizeof(time_str), "%d/%m/%Y %H:%M", localtime(&current->timestamp));
        
        printf("%-5d %-25s %-10s %-20s\n", 
               current->game_number, 
               current->guessed_animal, 
               status, 
               time_str);
        
        current = current->next;
    }
    printf("\n");
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

void save_history_to_file() {
    FILE* file = fopen(HISTORY_FILE, "w");
    if (file == NULL) return;
    
    GameHistory* current = game_history_head;
    while (current != NULL) {
        fprintf(file, "%d|%s|%d|%ld\n", 
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
    
    clear_game_history(); // Bersihkan list yang ada sebelum memuat
    
    char line[512];
    GameHistory* tail = NULL;

    while (fgets(line, sizeof(line), file)) {
        GameHistory* new_node = (GameHistory*)malloc(sizeof(GameHistory));
        if (new_node == NULL) continue;

        char* token;
        // Parsing data yang dipisahkan oleh '|'
        token = strtok(line, "|");
        if(token) new_node->game_number = atoi(token);

        token = strtok(NULL, "|");
        if(token) strncpy(new_node->guessed_animal, token, MAX_TEXT_LENGTH-1);

        token = strtok(NULL, "|");
        if(token) new_node->was_correct = atoi(token);

        token = strtok(NULL, "|");
        if(token) new_node->timestamp = atol(token);
        
        new_node->next = NULL;

        // Tambahkan ke akhir list agar urutan tetap sama seperti di file
        if (game_history_head == NULL) {
            game_history_head = new_node;
            tail = new_node;
        } else {
            tail->next = new_node;
            tail = new_node;
        }
    }
    fclose(file);
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
    print_header("STATISTIK PERMAINAN");
    
    int total_games = get_total_games();
    int correct_guesses = get_correct_guesses();
    double success_rate = get_success_rate();
    
    printf("Total Permainan      : %d\n", total_games);
    printf("Tebakan Benar        : %d\n", correct_guesses);
    printf("Tebakan Salah        : %d\n", total_games - correct_guesses);
    printf("Tingkat Keberhasilan : %.1f%%\n", success_rate);
    printf("\n");
}

void add_question_suggestion(const char* question, int was_successful) {
    // Cek apakah pertanyaan sudah ada, jika ya, update statistiknya
    QuestionSuggestion* current = suggestion_list;
    while (current != NULL) {
        if (strcmp(current->question, question) == 0) {
            current->usage_count++;
            // Update success rate menggunakan simple moving average
            double weight = 0.8;
            current->success_rate = (current->success_rate * weight) + ((was_successful ? 100.0 : 0.0) * (1.0 - weight));
            return;
        }
        current = current->next;
    }
    
    // Jika tidak ada, buat node baru
    QuestionSuggestion* new_suggestion = (QuestionSuggestion*)malloc(sizeof(QuestionSuggestion));
    if (new_suggestion == NULL) return;
    
    strncpy(new_suggestion->question, question, MAX_TEXT_LENGTH - 1);
    new_suggestion->question[MAX_TEXT_LENGTH - 1] = '\0';
    new_suggestion->usage_count = 1;
    new_suggestion->success_rate = was_successful ? 100.0 : 0.0;
    new_suggestion->next = suggestion_list;
    suggestion_list = new_suggestion;
}

char* get_best_question_suggestion() {
    if (suggestion_list == NULL) return "Tidak ada saran.";
    
    QuestionSuggestion* best = suggestion_list;
    QuestionSuggestion* current = suggestion_list->next;
    
    while (current != NULL) {
        // Skor = success_rate * bobot penggunaan
        double best_score = best->success_rate * (best->usage_count > 2 ? 1.0 : 0.5);
        double current_score = current->success_rate * (current->usage_count > 2 ? 1.0 : 0.5);
        if (current_score > best_score) {
            best = current;
        }
        current = current->next;
    }
    return best->question;
}