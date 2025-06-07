#ifndef UTILS_H
#define UTILS_H

#include "common_types.h"

// Fungsi untuk menampilkan UI dan menu
void print_separator();
void print_header(const char* title);
void print_main_menu();
int get_menu_choice(int max_choice);

// Fungsi untuk alur permainan
void print_welcome();
void print_goodbye();
void ready();
int play_again();

#endif // UTILS_H
