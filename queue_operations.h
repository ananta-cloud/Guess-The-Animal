#ifndef QUEUE_OPERATIONS_H
#define QUEUE_OPERATIONS_H

#include "common_types.h"

// Operasi Queue untuk manajemen pemain
PlayerQueue* create_player_queue();
void enqueue_player(PlayerQueue* queue, const char* name);
Player* dequeue_player(PlayerQueue* queue);
Player* peek_current_player(PlayerQueue* queue);
int is_queue_empty(PlayerQueue* queue);
void clear_player_queue(PlayerQueue* queue);

// Fungsi manajemen pemain
void rotate_to_next_player();
void update_player_stats(Player* player, int was_correct);

// Fungsi untuk setup mode permainan
int setup_multiplayer_mode();
int setup_single_player_mode();

// Fungsi untuk alur giliran pemain
void start_player_turn(Player* current_player);
void end_player_turn(Player* current_player, int was_correct);

#endif // QUEUE_OPERATIONS_H
