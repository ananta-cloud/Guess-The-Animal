#include "common_types.h"
#include "utils.h"

// Inisialisasi vaiabel global
GameHistory* game_history_head = NULL;
UndoStack* undo_stack_top = NULL;

// Utuk menghapus spasi pada string
void trim_string(char* str) {
    int len = strlen(str);
    
    // Hapus spasi dan baris baru di akhir
    while (len > 0 && (isspace(str[len-1]) || str[len-1] == '\n' || str[len-1] == '\r')) {
        str[len-1] = '\0';
        len--;
    }
    // Hapus spasi di awal
    int start = 0;
    while (str[start] && isspace(str[start])) {
        start++;
    }
    if (start > 0) {
        memmove(str, str + start, strlen(str + start) + 1);
    }
}

// Untuk mengubah string menjadi lowercase
void to_lowercase(char* str) {
    for (int i = 0; str[i]; i++) {
        str[i] = tolower(str[i]);
    }
}
// Untuk Membaca input dari pengguna
int get_answer() {
    char answer[20];
    
    if (fgets(answer, sizeof(answer), stdin) != NULL) {
        trim_string(answer);
        to_lowercase(answer);
        if (strcmp(answer, "yes") == 0 || strcmp(answer, "y") == 0 || strcmp(answer, "ya") == 0) {
            return 1; // Jawaban 'yes'
        } else if (strcmp(answer, "no") == 0 || strcmp(answer, "n") == 0 || strcmp(answer, "tidak") == 0) {
            return 0; // Jawaban 'no'
        } else {
            return -1; // Jawaban tidak valid
        }
    }
    return -1; // Error saat membaca input
}