#include "common_types.h"
#include "tree_operations.h"
#include "linked_list.h"
#include "utils.h"

// Variabel global untuk state permainan
TreeNodePtr root = NULL;
int game_counter = 1;

// Prototipe fungsi lokal
void play_game_session();
void play_single_round();

int main() {
    int main_choice;

    print_welcome();
    
    // Memuat database tree dan riwayat permainan saat program dimulai
    if (load_or_create_database(&root) != 0) {
        printf("Error: Gagal memuat database!\n");
        return 1;
    }
    load_history_from_file();
    // Set game_counter ke permainan berikutnya
    if(game_history_head != NULL) {
        GameHistory* current = game_history_head;
        while(current->next != NULL) current = current->next;
        game_counter = current->game_number + 1;
    }

    // Loop menu utama
    while (1) {
        print_main_menu();
        main_choice = get_menu_choice(3);
        
        switch (main_choice) {
            case 1:
                play_game_session();
                break;
            case 2:
                display_game_history();
                ready();
                break;
            case 3:
                print_goodbye();
                save_history_to_file(); // Simpan riwayat sebelum keluar
                free_tree(root);
                clear_game_history();
                return 0;
            default:
                printf("Pilihan tidak valid!\n");
        }
    }
}
/**
 * @brief Mengelola sesi permainan dimana user bisa bermain berulang kali.
 */
void play_game_session() {
    do {
        play_single_round();
    } while (play_again());
}

/**
 * @brief Menjalankan satu putaran penuh permainan, mulai dari bertanya hingga belajar.
 * @param root Pointer ke root dari pohon keputusan.
 */
void play_single_round() {
    TreeNodePtr last_node = NULL;
    int was_correct = 0;

    printf("\n-- GAME #%d --\n", game_counter);
    printf("Pikirkan seekor hewan, dan saya akan mencoba menebaknya!\n");
    
    choice(root, &last_node);

    if (last_node != NULL) {
        was_correct = ask_if_animal(last_node);
        
        if (was_correct) {
            printf("\nYeay! Saya berhasil menebak hewan Anda!\n");
        } else {
            build_question(last_node);
            auto_save_tree(root); // Simpan tree setelah belajar
        }
        
        // Tambahkan hasil permainan ke riwayat
        add_game_history(game_counter, last_node->text, was_correct);
        game_counter++;
    } else {
        printf("Error: Terjadi kesalahan dalam permainan!\n");
    }
}