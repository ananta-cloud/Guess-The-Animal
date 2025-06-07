#include "common_types.h"
#include "tree_operations.h"

// Prototipe fungsi lokal
void play_single_round(TreeNodePtr root);
int play_again();

int main() {
    TreeNodePtr root = NULL;

    printf("Selamat Datang di Animal Guessing Game!\n");
    printf("=======================================\n");

    // Membuat pohon keputusan awal
    root = create_default_tree();
    if (root == NULL) {
        printf("Error: Gagal membuat database awal!\n");
        return 1; // Keluar jika pembuatan tree gagal
    }

    // Loop permainan utama
    do {
        play_single_round(root);
    } while (play_again());

    // Membebaskan memori sebelum keluar
    free_tree(root);
    printf("\nTerima kasih telah bermain!\n");

    return 0;
}

/**
 * @brief Menjalankan satu putaran penuh permainan, mulai dari bertanya hingga belajar.
 * @param root Pointer ke root dari pohon keputusan.
 */
void play_single_round(TreeNodePtr root) {
    TreeNodePtr last_node = NULL;
    int was_correct = 0;

    printf("\n-- Babak Baru --\n");
    printf("Pikirkan seekor hewan, dan saya akan mencoba menebaknya!\n");
    
    // Mulai proses menebak dengan menavigasi tree
    choice(root, &last_node);

    if (last_node != NULL) {
        // Tanyakan konfirmasi untuk tebakan terakhir
        was_correct = ask_if_animal(last_node);
        
        if (was_correct) {
            printf("\nYeay! Saya berhasil menebak hewan Anda!\n");
        } else {
            // Jika salah, panggil fungsi untuk belajar
            build_question(last_node);

            if (auto_save_tree(root) == 0) {
                printf("Pembelajaran baru berhasil disimpan!\n");
            } else {
                printf("Peringatan: Gagal menyimpan pembelajaran baru!\n");
            }
        }
    } else {
        printf("Error: Terjadi kesalahan dalam permainan!\n");
    }
}

/**
 * @brief Menanyakan kepada pengguna apakah mereka ingin bermain lagi.
 * @return 1 jika ya, 0 jika tidak.
 */
int play_again() {
    printf("\nApakah Anda ingin bermain lagi? (yes/no): ");
    int answer = get_answer();
    
    if (answer == 1) {
        printf("Asyik! Mari bermain lagi!\n");
        return 1;
    } else {
        return 0;
    }
}
