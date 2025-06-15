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

// Modul untuk saran pertanyaan
void add_question_suggestion(const char* question, int was_successful);
char* get_best_question_suggestion();
void display_question_suggestions();
void update_question_success_rate(const char* question, int was_successful);
void clear_suggestions();

// Modul untuk riwayat
GameHistory* find_game_by_number(int game_number);
void display_recent_games(int count);

#endif // LINKED_LIST_H