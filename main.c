#include "../header.h"

// Global variables
TreeNodePtr root = NULL;
int game_counter = 1;
int is_multiplayer = 0;

// Function prototypes
void single_player_game();
void multiplayer_game();
void play_single_round();
void handle_statistics_menu();
void handle_admin_menu();
void handle_game_menu();

int main() {
    int main_choice;
    
    // Initialize system
    print_welcome();
    initialize_system();
    
    // Load or create database
    if (load_or_create_database(&root) != 0) {
        printf("Error: Gagal memuat database!\n");
        return 1;
    }
    
    // Main program loop
    while (1) {
        print_main_menu();
        main_choice = get_menu_choice(6);
        
        switch (main_choice) {
            case 1:
                single_player_game();
                break;
            case 2:
                multiplayer_game();
                break;
            case 3:
                handle_statistics_menu();
                break;
            case 4:
                handle_admin_menu();
                break;
            case 5:
                show_help_information();
                ready();
                break;
            case 6:
                printf("\n");
                display_session_summary();
                print_goodbye();
                cleanup_system();
                free_tree(root);
                return 0;
            default:
                printf("Pilihan tidak valid!\n");
        }
    }
}

void single_player_game() {
    is_multiplayer = 0;
    
    if (!setup_single_player_mode()) {
        printf("Gagal setup single player mode!\n");
        return;
    }
    
    handle_game_menu();
}

void multiplayer_game() {
    is_multiplayer = 1;
    
    if (!setup_multiplayer_mode()) {
        printf("Gagal setup multiplayer mode!\n");
        return;
    }
    
    handle_game_menu();
}

void handle_game_menu() {
    int game_choice;
    int continue_playing = 1;
    
    while (continue_playing) {
        print_game_menu();
        game_choice = get_menu_choice(5);
        
        switch (game_choice) {
            case 1:
                play_single_round();
                break;
            case 2:
                do {
                    play_single_round();
                } while (play_again());
                break;
            case 3:
                print_header("🐾 DAFTAR SEMUA HEWAN");
                display_all_animals(root);
                printf("\nTotal hewan dalam database: %d\n", count_total_animals(root));
                ready();
                break;
            case 4:
                display_game_statistics();
                if (is_multiplayer) {
                    display_all_players();
                }
                ready();
                break;
            case 5:
                continue_playing = 0;
                break;
            default:
                printf("Pilihan tidak valid!\n");
        }
    }
}

void play_single_round() {
    TreeNodePtr last_node = NULL;
    Player* current_player = NULL;
    int was_correct = 0;
    
    printf("\n");
    print_separator();
    printf("GAME #%d\n", game_counter);
    print_separator();
    
    // Handle multiplayer turn
    if (is_multiplayer) {
        current_player = peek_current_player(player_queue);
        if (current_player == NULL) {
            printf("Tidak ada player aktif!\n");
            return;
        }
        start_player_turn(current_player);
    } else {
        printf("Pikirkan seekor hewan, dan saya akan mencoba menebaknya!\n");
        ready();
    }
    
    // Start the guessing process
    choice(root, &last_node);
    
    if (last_node != NULL) {
        was_correct = ask_if_animal(last_node);
        
        if (was_correct) {
            printf("\nYeay! Saya berhasil menebak hewan Anda!\n");
            printf("Saya memang pintar, kan?\n");
        } else {
            printf("\nHmm, saya belum bisa menebak dengan benar.\n");
            printf("Mari bantu saya belajar!\n\n");
            build_question(last_node);
            
            // Auto-save after learning
            if (auto_save_tree(root) == 0) {
                printf("Pembelajaran berhasil disimpan!\n");
            }
        }
        
        // Add to game history
        add_game_history(game_counter, last_node->text, was_correct);
        
        // Update player stats if multiplayer
        if (is_multiplayer && current_player != NULL) {
            end_player_turn(current_player, was_correct);
            rotate_to_next_player(); // Move to next player
        }
        
        game_counter++;
    } else {
        printf("Error: Tidak dapat memproses permainan!\n");
    }
    
    printf("\n");
    ready();
}

void handle_statistics_menu() {
    int stats_choice;
    int continue_stats = 1;
    
    while (continue_stats) {
        print_statistics_menu();
        stats_choice = get_menu_choice(6);
        
        switch (stats_choice) {
            case 1:
                display_comprehensive_statistics();
                ready();
                break;
            case 2:
                display_game_history();
                ready();
                break;
            case 3:
                if (is_multiplayer || get_total_players() > 0) {
                    display_player_rankings();
                } else {
                    printf("Tidak ada data player untuk ranking.\n");
                    printf("Mainkan mode multiplayer untuk melihat ranking.\n");
                }
                ready();
                break;
            case 4:
                display_question_suggestions();
                
                char* best_question = get_best_question_suggestion();
                if (best_question != NULL) {
                    printf("Pertanyaan terbaik: \"%s\"\n", best_question);
                }
                ready();
                break;
            case 5:
                display_learning_analytics();
                ready();
                break;
            case 6:
                continue_stats = 0;
                break;
            default:
                printf("Pilihan tidak valid!\n");
        }
    }
}

void handle_admin_menu() {
    int admin_choice;
    int continue_admin = 1;
    
    while (continue_admin) {
        print_admin_menu();
        admin_choice = get_menu_choice(7);
        
        switch (admin_choice) {
            case 1:
                printf("\nINFORMASI TREE:\n");
                printf("   Kedalaman Tree: %d level\n", calculate_tree_depth(root));
                printf("   Total Hewan: %d\n", count_total_animals(root));
                printf("\n");
                
                iterative_preorder_traversal(root);
                ready();
                break;
                
            case 2:
                if (undo_last_operation(root)) {
                    printf("Menyimpan perubahan...\n");
                    auto_save_tree(root);
                } else {
                    printf("Tidak ada operasi yang dapat dibatalkan!\n");
                }
                ready();
                break;
                
            case 3:
                display_undo_history();
                ready();
                break;
                
            case 4:
                if (confirm_action("reset semua data")) {
                    reset_all_data();
                    
                    // Recreate default tree
                    free_tree(root);
                    root = create_default_tree();
                    if (root != NULL) {
                        auto_save_tree(root);
                        printf("Database default berhasil dibuat ulang!\n");
                    }
                    game_counter = 1;
                }
                ready();
                break;
                
            case 5:
                create_system_backup();
                ready();
                break;
                
            case 6:
                if (restore_system_backup()) {
                    // Reload tree from restored backup
                    free_tree(root);
                    if (load_or_create_database(&root) != 0) {
                        printf("Error setelah restore! Membuat database baru...\n");
                        root = create_default_tree();
                    }
                }
                ready();
                break;
                
            case 7:
                continue_admin = 0;
                break;
                
            default:
                printf("Pilihan tidak valid!\n");
        }
    }
}

// Additional utility functions for main program

void display_game_info() {
    printf("ℹ️  INFORMASI GAME:\n");
    printf("   Game Counter: %d\n", game_counter);
    printf("   Mode: %s\n", is_multiplayer ? "Multiplayer" : "Single Player");
    printf("   Total Hewan: %d\n", count_total_animals(root));
    printf("   Success Rate: %.1f%%\n", get_success_rate());
    printf("\n");
}

void handle_emergency_save() {
    printf("Menyimpan data darurat...\n");
    
    if (auto_save_tree(root) == 0) {
        printf("Tree berhasil disimpan!\n");
    }
    
    save_history_to_file();
    printf("History berhasil disimpan!\n");
}

// Signal handler for graceful shutdown (if needed)
void cleanup_on_exit() {
    printf("\nProgram dihentikan! Menyimpan data...\n");
    handle_emergency_save();
    cleanup_system();
    free_tree(root);
    exit(0);
}