#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include "common_types.h"

// Modul untuk Riwayat Permainan (Linked List)
void add_game_history(int game_number, const char* animal, int was_correct);
void display_game_history();
void clear_game_history();

// Modul untuk manajemen file riwayat
void save_history_to_file();
void load_history_from_file();

// Modul untuk statistik permainan
int get_total_games();
int get_correct_guesses();
double get_success_rate();
void display_game_statistics();

#endif // LINKED_LIST_H