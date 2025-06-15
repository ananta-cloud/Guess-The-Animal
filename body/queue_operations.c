#include "../header.h"

// Membuat antrian player baru
PlayerQueue* create_player_queue() {
    PlayerQueue* queue = (PlayerQueue*)malloc(sizeof(PlayerQueue));
    if (queue == NULL) {
        printf("Error: Tidak cukup memory untuk player queue!\n");
        return NULL;
    }
    
    queue->front = NULL;
    queue->rear = NULL;
    queue->count = 0;
    
    return queue;
}

// Input data player ke antrian
void enqueue_player(PlayerQueue* queue, const char* name) {
    if (queue == NULL) return;
    
    Player* new_player = (Player*)malloc(sizeof(Player));
    if (new_player == NULL) {
        printf("Error: Tidak cukup memory untuk player baru!\n");
        return;
    }
    strncpy(new_player->name, name, MAX_NAME_LENGTH - 1);
    new_player->name[MAX_NAME_LENGTH - 1] = '\0';
    new_player->score = 0;
    new_player->games_played = 0;
    new_player->correct_guesses = 0;
    new_player->next = NULL;
    if (queue->rear == NULL) {
        queue->front = new_player;
        queue->rear = new_player;
    } else {
        queue->rear->next = new_player;
        queue->rear = new_player;
    }
    queue->count++;
    printf("👤 Player '%s' berhasil ditambahkan ke antrian!\n", name);
}

// Hapus antrian player
Player* dequeue_player(PlayerQueue* queue) {
    if (queue == NULL || queue->front == NULL) {
        return NULL;
    }
    Player* front_player = queue->front;
    queue->front = queue->front->next;
    
    if (queue->front == NULL) {
        queue->rear = NULL;
    }
    queue->count--;
    front_player->next = NULL;
    return front_player;
}

// Lihat player saat ini
Player* peek_current_player(PlayerQueue* queue) {
    if (queue == NULL || queue->front == NULL) {
        return NULL;
    }
    return queue->front;
}

// Cek isi antrian
int is_queue_empty(PlayerQueue* queue) {
    return (queue == NULL || queue->front == NULL);
}

// Membersihkan data antrian player
void clear_player_queue(PlayerQueue* queue) {
    if (queue == NULL) return;
    
    while (!is_queue_empty(queue)) {
        Player* temp = dequeue_player(queue);
        if (temp) free(temp);
    }
    
    queue->count = 0;
    printf("Player queue telah dibersihkan.\n");
}

// Menambahkan player ke game
void add_player_to_game(const char* name) {
    if (player_queue == NULL) {
        player_queue = create_player_queue();
        if (player_queue == NULL) return;
    }
    // Cek jika player sudah diambil
    Player* current = player_queue->front;
    while (current != NULL) {
        if (strcmp(current->name, name) == 0) {
            printf("⚠️ Player '%s' sudah ada dalam antrian!\n", name);
            return;
        }
        current = current->next;
    }
    enqueue_player(player_queue, name);
}

// Ganti ke player selanjutnya
void rotate_to_next_player() {
    if (player_queue == NULL || is_queue_empty(player_queue)) return;
    // Pindah player saat ini ke belakang antrian
    Player* current = dequeue_player(player_queue);
    if (current != NULL) {
        enqueue_player(player_queue, current->name);
        // Copy stats player ke posisi baru
        Player* moved_player = player_queue->rear;
        moved_player->score = current->score;
        moved_player->games_played = current->games_played;
        moved_player->correct_guesses = current->correct_guesses;
        free(current);
    }
}

// Update score player
void update_player_score(Player* player, int points) {
    if (player == NULL) return;
    player->score += points;
    printf("%s mendapat %d poin! Total: %d\n", player->name, points, player->score);
}

// Update stats player
void update_player_stats(Player* player, int was_correct) {
    if (player == NULL) return;
    
    player->games_played++;
    if (was_correct) {
        player->correct_guesses++;
        update_player_score(player, 10); // 10 poin jika tebakan benar
    } else {
        update_player_score(player, 2);  // 2 poin untuk memainkan gamenya
    }
}

// Tampilkan player saat ini
void display_current_player() {
    Player* current = peek_current_player(player_queue);
    if (current == NULL) {
        printf("Tidak ada player aktif.\n");
        return;
    }
    printf("GILIRAN PLAYER: %s\n", current->name);
    printf("   Skor: %d\n", current->score);
    printf("   Games: %d\n", current->games_played);
    printf("   Benar: %d\n", current->correct_guesses);
    if (current->games_played > 0) {
        double success_rate = ((double)current->correct_guesses / current->games_played) * 100.0;
        printf("   Tingkat Sukses: %.1f%%\n", success_rate);
    }
    printf("\n");
}

// Tampilkan data semua player
void display_all_players() {
    if (player_queue == NULL || is_queue_empty(player_queue)) {
        printf("Tidak ada player yang terdaftar.\n");
        return;
    }
    print_header("DAFTAR SEMUA PLAYER");
    printf("%-20s %-8s %-8s %-8s %-12s\n", "Nama", "Skor", "Games", "Benar", "Sukses %");
    printf("---------------------------------------------------------------\n");
    Player* current = player_queue->front;
    while (current != NULL) {
        double success_rate = 0.0;
        if (current->games_played > 0) {
            success_rate = ((double)current->correct_guesses / current->games_played) * 100.0;
        }
        printf("%-20s %-8d %-8d %-8d %-12.1f\n", 
               current->name,
               current->score,
               current->games_played,
               current->correct_guesses,
               success_rate);
        current = current->next;
    }
    printf("\n");
}

// Tampilkan peringkat player
void display_player_rankings() {
    if (player_queue == NULL || is_queue_empty(player_queue)) {
        printf("Tidak ada player untuk ranking.\n");
        return;
    }
    // Buat array untuk sorting
    int player_count = player_queue->count;
    Player** players = (Player**)malloc(player_count * sizeof(Player*));
    if (players == NULL) {
        printf("Error: Tidak cukup memory untuk ranking!\n");
        return;
    }
    
    // Isi array
    Player* current = player_queue->front;
    for (int i = 0; i < player_count; i++) {
        players[i] = current;
        current = current->next;
    }
    
    // Sorting score ascending
    for (int i = 0; i < player_count - 1; i++) {
        for (int j = 0; j < player_count - i - 1; j++) {
            if (players[j]->score < players[j + 1]->score) {
                Player* temp = players[j];
                players[j] = players[j + 1];
                players[j + 1] = temp;
            }
        }
    }
    
    print_header("RANKING PLAYER");
    printf("%-5s %-20s %-8s %-8s %-12s\n", "Rank", "Nama", "Skor", "Games", "Sukses %");
    printf("----------------------------------------------------------\n");
    
    for (int i = 0; i < player_count; i++) {
        double success_rate = 0.0;
        if (players[i]->games_played > 0) {
            success_rate = ((double)players[i]->correct_guesses / players[i]->games_played) * 100.0;
        }
        char rank_icon[10];
        if (i == 0) strcpy(rank_icon, "🥇");
        else if (i == 1) strcpy(rank_icon, "🥈");
        else if (i == 2) strcpy(rank_icon, "🥉");
        else sprintf(rank_icon, "%d", i + 1);
        printf("%-5s %-20s %-8d %-8d %-12.1f\n", 
               rank_icon,
               players[i]->name,
               players[i]->score,
               players[i]->games_played,
               success_rate);
    }
    free(players);
    printf("\n");
}

// Inisialisasi mode multiplayer
int setup_multiplayer_mode() {
    char input[100];
    int player_count;
    print_header("SETUP MODE MULTIPLAYER");
    printf("Berapa jumlah player? (2-8): ");
    if (fgets(input, sizeof(input), stdin) != NULL) {
        player_count = atoi(input);
        if (player_count < 2 || player_count > 8) {
            printf("Jumlah player harus antara 2-8!\n");
            return 0;
        }
    } else {
        return 0;
    }
    if (player_queue != NULL) {
        clear_player_queue(player_queue);
        free(player_queue);
    }
    player_queue = create_player_queue();
    if (player_queue == NULL) return 0;
    for (int i = 0; i < player_count; i++) {
        printf("Masukkan nama player %d: ", i + 1);
        if (fgets(input, sizeof(input), stdin) != NULL) {
            trim_string(input);
            if (strlen(input) > 0) {
                add_player_to_game(input);
            } else {
                char default_name[20];
                sprintf(default_name, "Player%d", i + 1);
                add_player_to_game(default_name);
            }
        }
    }
    printf("\nSetup multiplayer selesai!\n");
    display_all_players();
    return 1;
}

// Inisialisasi untuk single mode
int setup_single_player_mode() {
    char input[100];
    print_header("SETUP MODE SINGLE PLAYER");
    if (player_queue != NULL) {
        clear_player_queue(player_queue);
        free(player_queue);
    }
    player_queue = create_player_queue();
    if (player_queue == NULL) return 0;
    printf("Masukkan nama Anda: ");
    if (fgets(input, sizeof(input), stdin) != NULL) {
        trim_string(input);
        if (strlen(input) > 0) {
            add_player_to_game(input);
        } else {
            add_player_to_game("Player1");
        }
    }
    printf("Setup single player selesai!\n\n");
    return 1;
}

// Untuk mulai giliran player
void start_player_turn(Player* current_player) {
    if (current_player == NULL) return;
    
    printf("\nGILIRAN: %s\n", current_player->name);
    printf("Pikirkan seekor hewan, dan saya akan mencoba menebaknya!\n\n");
}

// Untuk akhir giliran player
void end_player_turn(Player* current_player, int was_correct) {
    if (current_player == NULL) return;
    
    update_player_stats(current_player, was_correct);
    
    printf("\nStatistik %s:\n", current_player->name);
    printf("   Skor: %d\n", current_player->score);
    printf("   Games: %d\n", current_player->games_played);
    printf("   Benar: %d\n", current_player->correct_guesses);
}

// Mencari player terbaik 
Player* find_best_player() {
    if (player_queue == NULL || is_queue_empty(player_queue)) return NULL;
    
    Player* best = player_queue->front;
    Player* current = player_queue->front->next;
    
    while (current != NULL) {
        if (current->score > best->score) {
            best = current;
        }
        current = current->next;
    }
    
    return best;
}

// Menghitung total player
int get_total_players() {
    return (player_queue != NULL) ? player_queue->count : 0;
}