#include "common_types.h"

/**
 * @brief Menghapus spasi di awal/akhir dan karakter baris baru dari sebuah string.
 * @param str String yang akan di-trim.
 */
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

/**
 * @brief Mengubah sebuah string menjadi huruf kecil.
 * @param str String yang akan diubah.
 */
void to_lowercase(char* str) {
    for (int i = 0; str[i]; i++) {
        str[i] = tolower(str[i]);
    }
}
/**
 * @brief Membaca input dari pengguna dan mengonversinya menjadi jawaban 'yes' (1) atau 'no' (0).
 * @return 1 untuk 'yes', 0 untuk 'no', -1 untuk input tidak valid.
 */
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