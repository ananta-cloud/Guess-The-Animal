#ifndef UTILS_H
#define UTILS_H

#include "common_types.h"

// Fungsi untuk menampilkan UI dan menu
void print_separator();
void print_header(const char* title);
void print_game_menu();
void print_main_menu();
void print_admin_menu();

// Fungsi untuk alur permainan
int get_menu_choice(int max_choice);
void print_welcome();
void print_goodbye();
void ready();
int play_again();

// Fungsi sistem
void initialize_system();
void cleanup_system();

#endif // UTILS_H
