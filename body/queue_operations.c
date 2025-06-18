#include "../header/queue_operations.h"
#include "../header/utils.h"

// Membuat antrian player baru
PlayerQueue *create_player_queue()
{
    PlayerQueue *queue = (PlayerQueue *)malloc(sizeof(PlayerQueue));
    if (queue == NULL)
    {
        printf("Error: Tidak cukup memory untuk player queue!\n");
        return NULL;
    }

    queue->front = NULL;
    queue->rear = NULL;
    queue->count = 0;

    return queue;
}

// Input data player ke antrian
void enqueue_player(PlayerQueue *queue, const char *name)
{
    if (queue == NULL)
        return;

    Player *new_player = (Player *)malloc(sizeof(Player));
    if (new_player == NULL)
    {
        // Gunakan print_centered untuk konsistensi
        print_centered("Error: Tidak cukup memory untuk player baru!");
        return;
    }
    strncpy(new_player->name, name, MAX_NAME_LENGTH - 1);
    new_player->name[MAX_NAME_LENGTH - 1] = '\0';
    new_player->score = 0;
    new_player->games_played = 0;
    new_player->correct_guesses = 0;
    new_player->next = NULL;

    if (queue->rear == NULL)
    {
        queue->front = new_player;
        queue->rear = new_player;
    }
    else
    {
        queue->rear->next = new_player;
        queue->rear = new_player;
    }
    queue->count++;
    char message_buffer[256];
    sprintf(message_buffer, "Player '%s' berhasil ditambahkan ke antrian!", name);
    print_centered(message_buffer);
    printf("\n");
}

// Hapus antrian player
Player *dequeue_player(PlayerQueue *queue)
{
    if (queue == NULL || queue->front == NULL)
    {
        return NULL;
    }
    Player *front_player = queue->front;
    queue->front = queue->front->next;

    if (queue->front == NULL)
    {
        queue->rear = NULL;
    }
    queue->count--;
    front_player->next = NULL;
    return front_player;
}

// Lihat player saat ini
Player *peek_current_player(PlayerQueue *queue)
{
    if (queue == NULL || queue->front == NULL)
    {
        return NULL;
    }
    return queue->front;
}

// Cek isi antrian
int is_queue_empty(PlayerQueue *queue)
{
    return (queue == NULL || queue->front == NULL);
}

// Membersihkan data antrian player
void clear_player_queue(PlayerQueue *queue)
{
    if (queue == NULL)
        return;

    while (!is_queue_empty(queue))
    {
        Player *temp = dequeue_player(queue);
        if (temp)
            free(temp);
    }

    queue->count = 0;
    //printf("Player queue telah dibersihkan.\n");
}

// Menambahkan player ke game
void add_player_to_game(const char *name)
{
    if (player_queue == NULL)
    {
        player_queue = create_player_queue();
        if (player_queue == NULL)
            return;
    }
    // Cek jika player sudah diambil
    Player *current = player_queue->front;
    while (current != NULL)
    {
        if (strcmp(current->name, name) == 0)
        {
            char message_buffer[256];
            printf("\n");
            sprintf(message_buffer, "Player '%s' sudah ada dalam antrian!", name);
            print_centered(message_buffer);
            return;
        }
        current = current->next;
    }
    enqueue_player(player_queue, name);
}

// Ganti ke player selanjutnya
void rotate_to_next_player()
{
    if (player_queue == NULL || is_queue_empty(player_queue))
        return;
    // Pindah player saat ini ke belakang antrian
    Player *current = dequeue_player(player_queue);
    if (current != NULL)
    {
        enqueue_player(player_queue, current->name);
        // Copy stats player ke posisi baru
        Player *moved_player = player_queue->rear;
        moved_player->score = current->score;
        moved_player->games_played = current->games_played;
        moved_player->correct_guesses = current->correct_guesses;
        free(current);
    }
}

// Update score player
void update_player_score(Player *player, int points)
{
    if (player == NULL)
        return;
    player->score += points;
    
    char buffer[100];
    sprintf(buffer, "%s mendapat %d poin! Total: %d", player->name, points, player->score);
    print_aligned_prompt(buffer);
    printf("\n");
}

// Update stats player
void update_player_stats(Player *player, int was_correct)
{
    if (player == NULL)
        return;

    player->games_played++;
    if (was_correct)
    {
        player->correct_guesses++;
        update_player_score(player, 10); // 10 poin jika tebakan benar
    }
    else
    {
        update_player_score(player, 2); // 2 poin untuk memainkan gamenya
    }
}

// Tampilkan player saat ini
void display_current_player()
{
    Player *current = peek_current_player(player_queue);
    if (current == NULL)
    {
        printf("Tidak ada player aktif.\n");
        return;
    }
    printf("GILIRAN PLAYER: %s\n", current->name);
    printf("   Skor: %d\n", current->score);
    printf("   Games: %d\n", current->games_played);
    printf("   Benar: %d\n", current->correct_guesses);
    if (current->games_played > 0)
    {
        double success_rate = ((double)current->correct_guesses / current->games_played) * 100.0;
        printf("   Tingkat Sukses: %.1f%%\n", success_rate);
    }
    printf("\n");
}

// Tampilkan data semua player
void display_all_players()
{
    clear_screen();
    print_header("DAFTAR SEMUA PLAYER");

    if (player_queue == NULL || is_queue_empty(player_queue))
    {
        print_centered("Tidak ada player yang terdaftar.");
        return;
    }

    // --- Logika Perataan Tabel ---
    const int NAME_COL = 20, SCORE_COL = 8, GAMES_COL = 8, CORRECT_COL = 8, RATE_COL = 12;
    const int TABLE_WIDTH = NAME_COL + SCORE_COL + GAMES_COL + CORRECT_COL + RATE_COL + 4; // +4 spasi
    
    char separator[TABLE_WIDTH + 1];
    memset(separator, '-', TABLE_WIDTH);
    separator[TABLE_WIDTH] = '\0';

    int terminal_width = get_terminal_width();
    int padding = (terminal_width > TABLE_WIDTH) ? (terminal_width - TABLE_WIDTH) / 2 : 0;

    // --- Cetak Tabel dengan Rata Tengah ---
    for (int i = 0; i < padding; i++) { printf(" "); }
    printf("%-*s %-*s %-*s %-*s %-*s\n", NAME_COL, "Nama", SCORE_COL, "Skor", GAMES_COL, "Games", CORRECT_COL, "Benar", RATE_COL, "Sukses %");

    for (int i = 0; i < padding; i++) { printf(" "); }
    printf("%s\n", separator);

    Player *current = player_queue->front;
    while (current != NULL)
    {
        double success_rate = (current->games_played > 0) ? ((double)current->correct_guesses / current->games_played) * 100.0 : 0.0;
        
        for (int i = 0; i < padding; i++) { printf(" "); }
        printf("%-*s %-*d %-*d %-*d %-*.1f\n",
               NAME_COL, current->name,
               SCORE_COL, current->score,
               GAMES_COL, current->games_played,
               CORRECT_COL, current->correct_guesses,
               RATE_COL, success_rate);
        current = current->next;
    }
    printf("\n");
}

// Tampilkan peringkat player
// Di dalam body/queue_operations.c

void display_player_rankings()
{
    clear_screen();
    print_header("RANKING PLAYER");

    if (player_queue == NULL || is_queue_empty(player_queue))
    {
        print_centered("Tidak ada player untuk ranking.");
        return;
    }
    
    int player_count = player_queue->count;
    Player **players = (Player **)malloc(player_count * sizeof(Player *));
    if (players == NULL)
    {
        print_centered("Error: Tidak cukup memory untuk ranking!");
        return;
    }

    // (Logika untuk mengisi dan sorting array 'players' tetap sama)
    Player *current = player_queue->front;
    for (int i = 0; i < player_count; i++) {
        players[i] = current;
        current = current->next;
    }

    for (int i = 0; i < player_count - 1; i++) {
        for (int j = 0; j < player_count - i - 1; j++) {
            if (players[j]->score < players[j + 1]->score) {
                Player* temp = players[j];
                players[j] = players[j + 1];
                players[j + 1] = temp;
            }
        }
    }
    
    // --- Logika Perataan Tabel ---
    const int RANK_COL = 5, NAME_COL = 20, SCORE_COL = 8, GAMES_COL = 8, RATE_COL = 12;
    const int TABLE_WIDTH = RANK_COL + NAME_COL + SCORE_COL + GAMES_COL + RATE_COL + 4; // +4 spasi

    char separator[TABLE_WIDTH + 1];
    memset(separator, '-', TABLE_WIDTH);
    separator[TABLE_WIDTH] = '\0';
    
    int terminal_width = get_terminal_width();
    int padding = (terminal_width > TABLE_WIDTH) ? (terminal_width - TABLE_WIDTH) / 2 : 0;

    // --- Cetak Tabel dengan Rata Tengah ---
    for (int i = 0; i < padding; i++) { printf(" "); }
    printf("%-*s %-*s %-*s %-*s %-*s\n", RANK_COL, "Rank", NAME_COL, "Nama", SCORE_COL, "Skor", GAMES_COL, "Games", RATE_COL, "Sukses %");

    for (int i = 0; i < padding; i++) { printf(" "); }
    printf("%s\n", separator);

    for (int i = 0; i < player_count; i++)
    {
        double success_rate = (players[i]->games_played > 0) ? ((double)players[i]->correct_guesses / players[i]->games_played) * 100.0 : 0.0;
        char rank_icon[16];
        if (i == 0) strcpy(rank_icon, "1st");
        else if (i == 1) strcpy(rank_icon, "2nd");
        else if (i == 2) strcpy(rank_icon, "3rd");
        else snprintf(rank_icon, sizeof(rank_icon), "%d", i + 1);
        
        for (int j = 0; j < padding; j++) { printf(" "); }
        printf("%-*s %-*s %-*d %-*d %-*.1f\n",
               RANK_COL, rank_icon,
               NAME_COL, players[i]->name,
               SCORE_COL, players[i]->score,
               GAMES_COL, players[i]->games_played,
               RATE_COL, success_rate);
    }
    free(players);
    printf("\n");
}

// Inisialisasi mode multiplayer
int setup_multiplayer_mode()
{
    char input[100];
    int player_count;

    clear_screen();
    print_header("SETUP MODE MULTIPLAYER");
    print_aligned_prompt("Berapa jumlah player? (2-8): ");
    

    if (fgets(input, sizeof(input), stdin) != NULL)
    {
        player_count = atoi(input);
        if (player_count < 2 || player_count > 8)
        {
            print_centered("Jumlah player harus antara 2-8!");
            ready();
            return 0;
        }
    }
    else
    {
        return 0;
    }
    if (player_queue != NULL)
    {
        clear_player_queue(player_queue);
        free(player_queue);
    }
    player_queue = create_player_queue();
    if (player_queue == NULL)
        return 0;
    char prompt_buffer[100];
    for (int i = 0; i < player_count; i++)
    {
        printf("\n");
        sprintf(prompt_buffer, "Masukkan nama player %d: ", i + 1);
        print_aligned_prompt(prompt_buffer);

        if (fgets(input, sizeof(input), stdin) != NULL)
        {
            trim_string(input);
            if (strlen(input) > 0)
            {
                add_player_to_game(input);
            }
            else
            {
                char default_name[20];
                sprintf(default_name, "Player%d", i + 1);
                add_player_to_game(default_name);
            }
        }
    }
    printf("\n");
    print_centered("Setup multiplayer selesai!");
    display_all_players();
    ready();
    return 1;
}

// Inisialisasi untuk single mode
int setup_single_player_mode()
{
    char input[100];
    clear_screen();
    print_header("SETUP MODE SINGLE PLAYER");
    print_aligned_prompt("Masukkan nama Anda: ");

    if (fgets(input, sizeof(input), stdin) != NULL)
    {
        trim_string(input);
        if (strlen(input) > 0)
        {
            add_player_to_game(input);
        }
        else
        {
            add_player_to_game("Player1");
        }
    }
    printf("\n");
    print_centered("Setup single player selesai!");
    ready();
    return 1;
}

// Untuk mulai giliran player
void start_player_turn(Player *current_player)
{
    if (current_player == NULL)
        return;

    char buffer[100];
    
    // Mencetak baris GILIRAN dengan perataan
    sprintf(buffer, "GILIRAN: %s", current_player->name);
    print_aligned_prompt(buffer);
    printf("\n");

    // Mencetak baris instruksi dengan perataan
    print_aligned_prompt("Pikirkan seekor hewan, dan saya akan mencoba menebaknya!");
    printf("\n\n");
}

// Untuk akhir giliran player
void end_player_turn(Player *current_player, int was_correct)
{
    if (current_player == NULL)
        return;

    // Bagian update_player_stats akan secara otomatis memanggil
    // update_player_score yang sudah kita rapikan di langkah berikutnya.
    update_player_stats(current_player, was_correct);

    char buffer[100];

    // Mencetak blok statistik dengan perataan
    printf("\n"); // Memberi jarak
    sprintf(buffer, "Statistik %s:", current_player->name);
    print_aligned_prompt(buffer);
    printf("\n");

    sprintf(buffer, "   Skor: %d", current_player->score);
    print_aligned_prompt(buffer);
    printf("\n");

    sprintf(buffer, "   Games: %d", current_player->games_played);
    print_aligned_prompt(buffer);
    printf("\n");
    
    sprintf(buffer, "   Benar: %d", current_player->correct_guesses);
    print_aligned_prompt(buffer);
    printf("\n");
}

// Mencari player terbaik
Player *find_best_player()
{
    if (player_queue == NULL || is_queue_empty(player_queue))
        return NULL;

    Player *best = player_queue->front;
    Player *current = player_queue->front->next;

    while (current != NULL)
    {
        if (current->score > best->score)
        {
            best = current;
        }
        current = current->next;
    }

    return best;
}

// Menghitung total player
int get_total_players()
{
    return (player_queue != NULL) ? player_queue->count : 0;
}