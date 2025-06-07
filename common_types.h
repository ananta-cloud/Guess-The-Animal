#ifndef COMMON_TYPES_H
#define COMMON_TYPES_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_TEXT_LENGTH 256

// Tree Node for Animal Guessing
// Ini adalah satu-satunya struktur data yang kita butuhkan untuk memulai.
// 'text' akan berisi pertanyaan atau nama hewan.
// 'yes_ans' dan 'no_ans' adalah pointer ke node berikutnya.
// Jika 'yes_ans' dan 'no_ans' keduanya NULL, maka node ini adalah jawaban (hewan).
typedef struct TreeNode {
    char text[MAX_TEXT_LENGTH];
    struct TreeNode *yes_ans;
    struct TreeNode *no_ans;
} TreeNode;

typedef TreeNode* TreeNodePtr;

// Prototipe untuk fungsi utilitas dasar yang diperlukan untuk memproses input pengguna.
void trim_string(char* str);
void to_lowercase(char* str);
int get_answer();

#endif // COMMON_TYPES_H