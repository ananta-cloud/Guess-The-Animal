#ifndef COMMON_TYPES_H
#define COMMON_TYPES_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#define MAX_TEXT_LENGTH 256
#define MAX_NAME_LENGTH 50
#define DEFAULT_DB_FILE "animal_database.txt"
#define BACKUP_DB_FILE "animal_database_backup.txt"
#define HISTORY_FILE "game_history.txt"

// Tree Node for Animal Guessing
typedef struct TreeNode {
    char text[MAX_TEXT_LENGTH];
    struct TreeNode *yes_ans;
    struct TreeNode *no_ans;
} TreeNode;
typedef TreeNode* TreeNodePtr;

// Game History Node (Linked List)
typedef struct GameHistory {
    int game_number;
    char guessed_animal[MAX_TEXT_LENGTH];
    int was_correct;
    time_t timestamp;
    struct GameHistory* next;
} GameHistory;

// Undo Stack Node
typedef struct UndoStack {
    TreeNodePtr modified_node;
    char original_text[MAX_TEXT_LENGTH];
    TreeNodePtr original_yes;
    TreeNodePtr original_no;
    char operation_type[20]; // "LEARN", "MODIFY", etc.
    struct UndoStack* next;
} UndoStack;

// Player Queue Node
typedef struct Player {
    char name[MAX_NAME_LENGTH];
    int score;
    int games_played;
    int correct_guesses;
    struct Player* next;
} Player;
typedef struct PlayerQueue {
    Player* front;
    Player* rear;
    int count;
} PlayerQueue;

// Question Suggestion Node (Linked List)
typedef struct QuestionSuggestion {
    char question[MAX_TEXT_LENGTH];
    int usage_count;
    double success_rate;
    struct QuestionSuggestion* next;
} QuestionSuggestion;

// Global variables
extern GameHistory* game_history_head;
extern UndoStack* undo_stack_top;
extern PlayerQueue* player_queue;
extern QuestionSuggestion* suggestion_list;

// Common utility functions 
void trim_string(char* str);
void to_lowercase(char* str);
int get_answer();

#endif
