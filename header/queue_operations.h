#ifndef QUEUE_OPERATIONS_H
#define QUEUE_OPERATIONS_H

#include "../header.h"

// Operasi Queue untuk manajemen pemain
PlayerQueue* create_player_queue();
void enqueue_player(PlayerQueue* queue, const char* name);
Player* dequeue_player(PlayerQueue* queue);
Player* peek_current_player(PlayerQueue* queue);
int is_queue_empty(PlayerQueue* queue);
void clear_player_queue(PlayerQueue* queue);

// Fungsi manajemen pemain
void rotate_to_next_player();
void update_player_score(Player* player, int points);
void update_player_stats(Player* player, int was_correct);
void display_current_player();
void display_all_players();
void display_player_rankings();

// Fungsi untuk setup mode permainan
int setup_multiplayer_mode();
int setup_single_player_mode();

// Fungsi untuk alur giliran pemain
void start_player_turn(Player* current_player);
void end_player_turn(Player* current_player, int was_correct);

// Fungsi statistik dan utilitas pemain
Player* find_best_player();
Player* find_player_by_name(const char* name);
void save_player_stats();
void load_player_stats();
int get_total_players();

#endif // QUEUE_OPERATIONS_H