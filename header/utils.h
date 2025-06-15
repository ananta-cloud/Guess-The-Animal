#ifndef UTILS_H
#define UTILS_H

#include "common_types.h"

// Menu and UI functions
void print_main_menu();
void print_game_menu();
void print_statistics_menu();
void print_admin_menu();
int get_menu_choice(int max_choice);

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