#include "queue_operations.h"

// Membuat antrian player baru
PlayerQueue* create_player_queue() {
    PlayerQueue* queue = (PlayerQueue*)malloc(sizeof(PlayerQueue));
    if (queue == NULL) return NULL;
    queue->front = NULL;
    queue->rear = NULL;
    queue->count = 0;
    return queue;
}

// Menambahkan data pemain ke akhir antrean (enqueue)
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
    printf("Pemain '%s' ditambahkan ke permainan!\n", name);
}

// Menghapus data antrian pemain dari depan
Player* dequeue_player(PlayerQueue* queue) {
    if (queue == NULL || queue->front == NULL) return NULL;
    
    Player* front_player = queue->front;
    queue->front = queue->front->next;
    
    if (queue->front == NULL) queue->rear = NULL;
    
    queue->count--;
    front_player->next = NULL; 
    return front_player;
}

// Melihat data pemain
Player* peek_current_player(PlayerQueue* queue) {
    if (queue == NULL) return NULL;
    return queue->front;
}

// Mengecek antrian Kosong/Tidak
int is_queue_empty(PlayerQueue* queue) {
    return (queue == NULL || queue->count == 0);
}

// Membersihkan data pemain
void clear_player_queue(PlayerQueue* queue) {
    if (queue == NULL) return;
    while (!is_queue_empty(queue)) {
        Player* temp = dequeue_player(queue);
        if (temp) free(temp);
    }
}

/**
 * @brief Memindahkan pemain saat ini ke belakang antrean.
 */
void rotate_to_next_player() {
    if (player_queue == NULL || player_queue->count <= 1) return;
    
    Player* current_player = dequeue_player(player_queue);
    if(current_player) {
         // Re-enqueue pemain dengan data yang sama
        enqueue_player(player_queue, current_player->name);
        player_queue->rear->score = current_player->score;
        player_queue->rear->games_played = current_player->games_played;
        player_queue->rear->correct_guesses = current_player->correct_guesses;
        free(current_player);
    }
}

/**
 * @brief Memperbarui statistik pemain setelah satu ronde.
 * @param player Pemain yang statistiknya akan diperbarui.
 * @param was_correct Apakah tebakan benar.
 */
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
    printf("Berapa jumlah pemain? (2-4): ");
    if (fgets(input, sizeof(input), stdin) == NULL) return 0;
    player_count = atoi(input);
    if (player_count < 2 || player_count > 4) {
        printf("Jumlah pemain tidak valid!\n");
        return 0;
    }

    if (player_queue != NULL) clear_player_queue(player_queue);
    else player_queue = create_player_queue();
    
    for (int i = 0; i < player_count; i++) {
        printf("Masukkan nama pemain %d: ", i + 1);
        fgets(input, sizeof(input), stdin);
        trim_string(input);
        enqueue_player(player_queue, strlen(input) > 0 ? input : "Player");
    }
    printf("\nSetup multiplayer selesai!\n");
    return 1;
}

/**
 * @brief Mengatur permainan untuk mode single player.
 * @return 1 jika berhasil.
 */
int setup_single_player_mode() {
    if (player_queue != NULL) clear_player_queue(player_queue);
    else player_queue = create_player_queue();
    enqueue_player(player_queue, "Player 1"); // Pemain default
    return 1;
}

// Menampilkan pesan start giliran pada pemain
void start_player_turn(Player* current_player) {
    if (current_player == NULL) return;
    printf("\n--- GILIRAN: %s ---\n", current_player->name);
    printf("Pikirkan seekor hewan, dan saya akan mencoba menebaknya!\n");
}

// Menampilkan pesan akhir giliran untuk diupdate di statistik pemain
void end_player_turn(Player* current_player, int was_correct) {
    if (current_player == NULL) return;
    
    update_player_stats(current_player, was_correct);
    printf("\nGiliran %s selesai. Skor: %d\n", current_player->name, current_player->score);
}
