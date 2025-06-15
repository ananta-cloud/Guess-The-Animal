#ifndef COMMON_TYPES_H
#define COMMON_TYPES_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#define MAX_TEXT_LENGTH 256
#define MAX_NAME_LENGTH 128
#define DEFAULT_DB_FILE "animal_database.txt" // File untuk menyimpan data hewan
#define BACKUP_DB_FILE "animal_database_backup.txt" // File untuk backup data di database hewan
#define HISTORY_FILE "game_history.txt" // File untuk menyimpan riwayat permainan

// Tree Node untuk Menebak Hewan
typedef struct TreeNode {
    char text[MAX_TEXT_LENGTH];
    struct TreeNode *yes_ans;
    struct TreeNode *no_ans;
} TreeNode;
typedef TreeNode* TreeNodePtr;

// Node game history untuk linked list
typedef struct GameHistory{
    int game_number;
    char guessed_animal[MAX_TEXT_LENGTH];
    int was_correct;
    time_t timestamp;
    struct GameHistory* next;
} GameHistory;
extern GameHistory* game_history_head;

// Node Undo untuk stack
typedef struct UndoStack {
    TreeNodePtr modified_node;
    char original_text[MAX_TEXT_LENGTH];
    TreeNodePtr original_yes;
    TreeNodePtr original_no;
    char operation_type[20]; // "LEARN"
    struct UndoStack* next;
} UndoStack;
extern UndoStack* undo_stack_top;

// Node Untuk Player
typedef struct Player {
    char name[MAX_NAME_LENGTH];
    int score;
    int games_played;
    int correct_guesses;
    struct Player* next;
} Player;

// Node untuk Antrian Player
typedef struct PlayerQueue {
    Player* front;
    Player* rear;
    int count;
} PlayerQueue;
extern PlayerQueue* player_queue;

// Node untuk Pertanyaan
typedef struct QuestionSuggestion {
    char question[MAX_TEXT_LENGTH];
    int usage_count;
    double success_rate;
    struct QuestionSuggestion* next;
} QuestionSuggestion;
extern QuestionSuggestion* suggestion_list;

// Prototipe untuk fungsi utilitas dasar yang diperlukan untuk memproses input pengguna.
void trim_string(char* str);
void to_lowercase(char* str);
int get_answer();
void print_header(const char* title);
void print_separator();

#endif // COMMON_TYPES_H