#ifndef UTILS_H
#define UTILS_H

#include "common_types.h"

// Fungsi untuk menampilkan UI dan menu
void print_separator();
void print_header(const char* title);
void print_game_menu();
void print_main_menu();
void print_statistics_menu();
void print_admin_menu();
int get_menu_choice(int max_choice);

// Fungsi untuk alur permainan
void print_welcome();
void print_goodbye();
void ready();
int play_again();

// Fungsi sistem
void initialize_system();
void cleanup_system();
void reset_all_data();
int create_system_backup();
int restore_system_backup();
int confirm_action(const char* action);

// --- FUNGSI TAMPILAN BARU ---
void display_comprehensive_statistics();
void display_learning_analytics();
void show_help_information();
void display_session_summary();

// --- FUNGSI VALIDASI INPUT BARU ---
int get_valid_integer(int min, int max);
void get_valid_string(char* buffer, int max_length, const char* prompt);

// --- FUNGSI TAMPILAN BARU ---
void display_system_status();

// --- FUNGSI UTILITAS WAKTU BARU ---
char* format_timestamp(time_t timestamp);
int get_days_since_last_play();

#endif // UTILS_H
