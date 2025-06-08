#include "queue_operations.h"
#include "utils.h"

// Membuat antrian player baru
PlayerQueue* create_player_queue() {
    PlayerQueue* queue = (PlayerQueue*)malloc(sizeof(PlayerQueue));
    if (queue == NULL) return NULL;
    queue->front = NULL;
    queue->rear = NULL;
    queue->count = 0;
    return queue;
}

// Menambahkan data Player ke akhir antrean (enqueue)
void enqueue_player(PlayerQueue* queue, const char* name) {
    if (queue == NULL) return;
    Player* new_player = (Player*)malloc(sizeof(Player));
    if (new_player == NULL) return;
    strncpy(new_player->name, name, MAX_NAME_LENGTH - 1);
    new_player->name[MAX_NAME_LENGTH - 1] = '\0';
    new_player->score = 0;
    new_player->games_played = 0;
    new_player->correct_guesses = 0;
    new_player->next = NULL;
    
    if (queue->rear == NULL) { // Jika antrean kosong
        queue->front = new_player;
        queue->rear = new_player;
    } else {
        queue->rear->next = new_player;
        queue->rear = new_player;
    }
    queue->count++;
    printf("Player '%s' ditambahkan ke permainan!\n", name);
}

// Menghapus data antrian Player dari depan
Player* dequeue_player(PlayerQueue* queue) {
    if (queue == NULL || queue->front == NULL) return NULL;
    
    Player* front_player = queue->front;
    queue->front = queue->front->next;
    
    if (queue->front == NULL) queue->rear = NULL;
    
    queue->count--;
    front_player->next = NULL; 
    return front_player;
}

// Melihat data Player
Player* peek_current_player(PlayerQueue* queue) {
    if (queue == NULL) return NULL;
    return queue->front;
}

// Mengecek antrian Kosong/Tidak
int is_queue_empty(PlayerQueue* queue) {
    return (queue == NULL || queue->count == 0);
}

// Membersihkan data Player
void clear_player_queue(PlayerQueue* queue) {
    if (queue == NULL) return;
    while (!is_queue_empty(queue)) {
        Player* temp = dequeue_player(queue);
        if (temp) free(temp);
    }
}

// Memindahkan Player ke antrian belakang
void rotate_to_next_player() {
    if (player_queue == NULL || player_queue->count <= 1) return;
    
    Player* current_player = dequeue_player(player_queue);
    if(current_player) {
         // Re-enqueue Player dengan data yang sama
        enqueue_player(player_queue, current_player->name);
        player_queue->rear->score = current_player->score;
        player_queue->rear->games_played = current_player->games_played;
        player_queue->rear->correct_guesses = current_player->correct_guesses;
        free(current_player);
    }
}

// Update statistika player
void update_player_stats(Player* player, int was_correct) {
    if (player == NULL) return;
    
    player->games_played++;
    if (was_correct) {
        player->correct_guesses++;
        player->score += 10;
    } else {
        player->score += 2; // Poin partisipasi
    }
}

/**
 * @brief Mengatur permainan untuk mode multiplayer.
 * @return 1 jika berhasil, 0 jika gagal.
 */
int setup_multiplayer_mode() {
    char input[100];
    int player_count;
    
    print_header("SETUP MODE MULTIPLAYER");
    printf("Berapa jumlah Player? (2-4): ");
    if (fgets(input, sizeof(input), stdin) == NULL) return 0;
    player_count = atoi(input);
    if (player_count < 2 || player_count > 4) {
        printf("Jumlah Player tidak valid!\n");
        return 0;
    }

    if (player_queue != NULL) clear_player_queue(player_queue);
    else player_queue = create_player_queue();
    
    for (int i = 0; i < player_count; i++) {
        printf("Masukkan nama Player %d: ", i + 1);
        fgets(input, sizeof(input), stdin);
        trim_string(input);
        enqueue_player(player_queue, strlen(input) > 0 ? input : "Player");
    }
    printf("\nSetup multiplayer selesai!\n");
    return 1;
}

// Setting untuk single Player
int setup_single_player_mode() {
    if (player_queue != NULL) clear_player_queue(player_queue);
    else player_queue = create_player_queue();
    enqueue_player(player_queue, "Player 1"); // Player default
    return 1;
}

// Menampilkan pesan start giliran pada Player
void start_player_turn(Player* current_player) {
    if (current_player == NULL) return;
    printf("\n--- GILIRAN: %s ---\n", current_player->name);
    printf("Pikirkan seekor hewan, dan saya akan mencoba menebaknya!\n");
}

// Menampilkan pesan akhir giliran untuk diupdate di statistik Player
void end_player_turn(Player* current_player, int was_correct) {
    if (current_player == NULL) return;
    
    update_player_stats(current_player, was_correct);
    printf("\nGiliran %s selesai. Skor: %d\n", current_player->name, current_player->score);
}

// Menampilkan daftar semua Player beserta statistik mereka
void display_all_players() {
    if (player_queue == NULL || is_queue_empty(player_queue)) {
        printf("Tidak ada Player yang terdaftar.\n");
        return;
    }
    
    print_header("DAFTAR SEMUA Player");
    printf("%-20s %-8s %-8s\n", "Nama", "Skor", "Main");
    printf("----------------------------------------\n");
    
    Player* current = player_queue->front;
    while (current != NULL) {
        printf("%-20s %-8d %-8d\n", 
               current->name, current->score, current->games_played);
        current = current->next;
    }
    printf("\n");
}

// Menampilkan peringkat Player berdasarkan skor tertinggi
void display_player_rankings() {
    if (player_queue == NULL || is_queue_empty(player_queue)) {
        printf("Tidak ada Player untuk diperingkatkan.\n");
        return;
    }
    
    int count = player_queue->count;
    Player** players = (Player**)malloc(count * sizeof(Player*));
    if (players == NULL) { printf("Gagal alokasi memori untuk ranking!\n"); return; }
    
    // Salin pointer Player dari queue ke array
    Player* current = player_queue->front;
    for (int i = 0; i < count; i++) {
        players[i] = current;
        current = current->next;
    }
    
    // Urutkan array menggunakan Bubble Sort (cukup untuk jumlah Player kecil)
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (players[j]->score < players[j+1]->score) {
                Player* temp = players[j];
                players[j] = players[j+1];
                players[j+1] = temp;
            }
        }
    }
    
    print_header("RANKING Player");
    printf("%-5s %-20s %-8s\n", "Rank", "Nama", "Skor");
    printf("------------------------------------\n");
    for (int i = 0; i < count; i++) {
        printf("%-5d %-20s %-8d\n", i + 1, players[i]->name, players[i]->score);
    }
    
    free(players);
    printf("\n");
}

// Untuk menemukan Player dengan score tertinggi
Player* find_best_player() {
    if (player_queue == NULL || is_queue_empty(player_queue)) {
        return NULL;
    }
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

// Untuk menghitung total Player
int get_total_players() {
    if (player_queue == NULL) {
        return 0;
    }
    return player_queue->count;
}