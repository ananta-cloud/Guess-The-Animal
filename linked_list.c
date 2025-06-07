#include "linked_list.h"

/**
 * @brief Menambahkan entri baru ke awal linked list riwayat permainan.
 * @param game_number Nomor urut permainan.
 * @param animal Nama hewan yang ditebak.
 * @param was_correct Status apakah tebakan benar (1) atau salah (0).
 */
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

/**
 * @brief Menampilkan semua riwayat permainan yang tersimpan di linked list.
 */
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

/**
 * @brief Membebaskan semua memori yang digunakan oleh linked list riwayat.
 */
void clear_game_history() {
    GameHistory* current = game_history_head;
    while (current != NULL) {
        GameHistory* temp = current;
        current = current->next;
        free(temp);
    }
    game_history_head = NULL;
}

/**
 * @brief Menyimpan seluruh riwayat permainan dari linked list ke file.
 */
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

/**
 * @brief Memuat riwayat permainan dari file ke dalam linked list.
 */
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
