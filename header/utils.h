#ifndef UTILS_H
#define UTILS_H

#include "common_types.h"
#include <conio.h>

// Menu and UI functions
void print_main_menu(int highlighted_option);
void print_game_menu(int highlighted_option);
void print_statistics_menu(int highlighted_option);
void print_admin_menu(int highlighted_option);
int get_menu_selection(int max_choice, void (*print_menu_func)(int));
void print_centered(const char* text);
void prompt_centered(const char* text);
void print_aligned_prompt(const char* prompt);
void clear_screen();
int get_terminal_width();

// Game flow functions
void print_welcome();
void print_goodbye();
void ready();
int play_again();
void display_game_rules();

// System functions
void initialize_system();
void cleanup_system();
void reset_all_data();
int create_system_backup();
int restore_system_backup();

// Input validation functions
int get_valid_integer(int min, int max);
void get_valid_string(char* buffer, int max_length, const char* prompt);
int confirm_action(const char* action);

// Display functions
void display_comprehensive_statistics();
void display_learning_analytics();
void display_system_status();
void show_help_information();

// Time utility functions
char* format_timestamp(time_t timestamp);
int get_days_since_last_play();
void display_session_summary();

#endif