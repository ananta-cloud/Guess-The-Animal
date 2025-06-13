#include "common_types.h"

// Global variables initialization
GameHistory* game_history_head = NULL;
UndoStack* undo_stack_top = NULL;
PlayerQueue* player_queue = NULL;
QuestionSuggestion* suggestion_list = NULL;

void trim_string(char* str) {
    int len = strlen(str);
    
    // Remove trailing whitespace and newline
    while (len > 0 && (isspace(str[len-1]) || str[len-1] == '\n' || str[len-1] == '\r')) {
        str[len-1] = '\0';
        len--;
    }
    
    // Remove leading whitespace
    int start = 0;
    while (str[start] && isspace(str[start])) {
        start++;
    }
    
    if (start > 0) {
        memmove(str, str + start, strlen(str + start) + 1);
    }
}

void to_lowercase(char* str) {
    for (int i = 0; str[i]; i++) {
        str[i] = tolower(str[i]);
    }
}

int get_answer() {
    char answer[20];
    
    if (fgets(answer, sizeof(answer), stdin) != NULL) {
        trim_string(answer);
        to_lowercase(answer);
        
        if (strcmp(answer, "yes") == 0 || strcmp(answer, "y") == 0 || 
            strcmp(answer, "ya") == 0 || strcmp(answer, "iya") == 0 || strcmp(answer, "benar") == 0
            || strcmp(answer, "bener") == 0){
            return 1;
        } else if (strcmp(answer, "no") == 0 || strcmp(answer, "n") == 0 || 
                   strcmp(answer, "tidak") == 0 || strcmp(answer, "nggak") == 0 || strcmp(answer, "gak") == 0
                   || strcmp(answer, "g") == 0 || strcmp(answer, "salah") == 0 || strcmp(answer, "bukan") == 0) {
            return 0;
        } else {
            return -1; // Invalid answer
        }
    }
    return -1;
}
