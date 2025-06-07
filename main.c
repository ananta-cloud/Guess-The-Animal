#include "common_types.h"
#include "tree_operations.h"
#include "linked_list.h"
#include "stack_operations.h"
#include "queue_operations.h"
#include "utils.h"

// Variabel global untuk state permainan
TreeNodePtr root = NULL;
int game_counter = 1;
int is_multiplayer = 0;

// Prototipe fungsi lokal
void single_player_game();
void multiplayer_game();
void play_single_round();
void handle_game_menu();
void handle_admin_menu();

int main() {
    int main_choice;

    print_welcome();
    initialize_system();
    
    // Memuat database tree dan riwayat permainan saat program dimulai
    if (load_or_create_database(&root) != 0) {
        printf("Error: Gagal memuat database!\n");
        return 1;
    }

    while (1) {
        print_main_menu();
        main_choice = get_menu_choice(5);
        
        switch (main_choice) {
            case 1: 
                single_player_game(); 
                break;
            case 2: 
                multiplayer_game(); 
                break;
            case 3: 
                display_game_history(); 
                ready(); 
                break;
            case 4: 
                handle_admin_menu(); 
                break;
            case 5:
                print_goodbye();
                cleanup_system();
                free_tree(root);
                return 0;
            default: printf("Pilihan tidak valid!\n");
        }
    }
}

void single_player_game() {
    is_multiplayer = 0;
    setup_single_player_mode();
    handle_game_menu();
}

void multiplayer_game() {
    is_multiplayer = 1;
    if (!setup_multiplayer_mode()) {
        printf("Gagal memulai mode multiplayer!\n");
        return;
    }
    handle_game_menu();
}

void handle_game_menu() {
    int game_choice;
    while (1) {
        print_game_menu();
        game_choice = get_menu_choice(4);
        
        switch (game_choice) {
            case 1: play_single_round(); break;
            case 2: do { play_single_round(); } while (play_again()); break;
            case 3: // Tampilkan semua hewan
                print_header("DAFTAR SEMUA HEWAN DI DATABASE");
                display_all_animals(root);
                printf("\nTotal hewan diketahui: %d\n", count_total_animals(root));
                ready();
                break;
            case 4: return;
            default: printf("Pilihan tidak valid!\n");
        }
    }
}

/**
 * @brief Menangani navigasi dan logika untuk menu statistik.
 */
void handle_statistics_menu() {
    int stats_choice;
    while (1) {
        print_statistics_menu();
        stats_choice = get_menu_choice(4);

        switch(stats_choice) {
            case 1:
                display_game_statistics();
                printf("STATISTIK DATABASE:\n");
                printf("   Total hewan diketahui: %d\n", count_total_animals(root));
                printf("   Kedalaman pengetahuan: %d level\n", calculate_tree_depth(root));
                ready();
                break;
            case 2:
                display_game_history();
                ready();
                break;
            case 3:
                display_player_rankings();
                ready();
                break;
            case 4:
                return; // Kembali
        }
    }
}

void play_single_round() {
    TreeNodePtr last_node = NULL;
    Player* current_player = NULL;
    int was_correct = 0;

    printf("\n-- GAME #%d --\n", game_counter);

    if (is_multiplayer) {
        current_player = peek_current_player(player_queue);
        start_player_turn(current_player);
    } else {
        printf("Pikirkan seekor hewan, saya akan menebaknya!\n");
    }
    
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
        if (is_multiplayer) {
            end_player_turn(current_player, was_correct);
            rotate_to_next_player();
        }
        game_counter++;
    } else {
        printf("Error: Terjadi kesalahan!\n");
    }
    ready();
}

void handle_admin_menu() {
    int admin_choice;
    print_admin_menu();
    admin_choice = get_menu_choice(2);

    switch (admin_choice) {
        case 1:
            if (undo_last_operation(root)) {
                auto_save_tree(root);
            }
            break;
        case 2: return;
    }
    ready();
}