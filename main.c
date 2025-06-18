#include "header/common_types.h"
#include "header/tree_operations.h"
#include "header/linked_list.h"
#include "header/stack_operations.h"
#include "header/queue_operations.h"
#include "header/utils.h"
#include <math.h>

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

int main()
{
    int main_choice;

    // Initialize system
    //print_welcome();
initialize_system();
    // Load or create database
    if (load_or_create_database(&root) != 0)
    {
        print_centered("Error: Gagal memuat database!");
        return 1;
    }

    // Main program loop
    while (1)
    {
        main_choice = get_menu_selection(6, print_main_menu);

        switch (main_choice)
        {
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
            display_session_summary();
            print_goodbye();
            cleanup_system();
            free_tree(root);
            return 0;
        default:
            print_centered("Pilihan tidak valid!");
            ready();
        }
    }
}

void single_player_game()
{
    is_multiplayer = 0;

    if (!setup_single_player_mode())
    {
        printf("Gagal setup single player mode!\n");
        return;
    }

    handle_game_menu();
}

void multiplayer_game()
{
    is_multiplayer = 1;

    if (!setup_multiplayer_mode())
    {
        printf("Gagal setup multiplayer mode!\n");
        return;
    }

    handle_game_menu();
}

void handle_game_menu()
{
    int game_choice;
    int continue_playing = 1;

    while (continue_playing)
    {
        game_choice = get_menu_selection(5, print_game_menu);

        switch (game_choice)
        {
        case 1:
            play_single_round();
            break;
        case 2:
            do
            {
                play_single_round();
            } while (play_again());
            break;
        case 3:
            print_header("DAFTAR SEMUA HEWAN");
            display_all_animals(root);
            char buffer[100];
            sprintf(buffer, "Total hewan dalam database: %d", count_total_animals(root));
            printf("\n");             
            print_aligned_prompt(buffer);
            printf("\n");
            ready();
            break;
        case 4:
            display_game_statistics();
            if (is_multiplayer)
            {
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

void play_single_round()
{
    TreeNodePtr last_node = NULL;
    Player *current_player = NULL;
    int was_correct = 0;
    clear_screen();
    char header_buffer[50];
    sprintf(header_buffer, "GAME #%d", game_counter);
    print_header(header_buffer);

    // Handle giliran multiplayer
    if (is_multiplayer)
    {
        current_player = peek_current_player(player_queue);
        if (current_player == NULL)
        {
            print_centered("Tidak ada player aktif!");
            ready();
            return;
        }
        start_player_turn(current_player);
    }
    else // Mode Single Player
    {
        print_aligned_prompt("Pikirkan seekor hewan, dan saya akan mencoba menebaknya!");
        printf("\n");
        print_aligned_prompt("Tekan ENTER untuk memulai...");
        int c;
        while ((c = getchar()) != '\n' && c != EOF)
        {
        }
        getchar();
        printf("\n");
    }

    // Mulai proses menebak
    choice(root, &last_node);

    if (last_node != NULL)
    {
        was_correct = ask_if_animal(last_node);
        if (was_correct)
        {
            printf("\n");
            print_aligned_prompt("Yeay! Saya berhasil menebak hewan Anda!");
            printf("\n");
            print_aligned_prompt("Saya memang pintar, kan?");
            printf("\n");
        }
        else
        {
            printf("\n");
            print_aligned_prompt("Hmm, saya belum bisa menebak dengan benar.");
            printf("\n");
            print_aligned_prompt("Mari bantu saya belajar!");
            printf("\n\n");

            build_question(last_node);

            if (auto_save_tree(root) == 0)
            {
                printf("\n");
                print_aligned_prompt("Pembelajaran berhasil disimpan!");
                printf("\n");
            }
        }
        add_game_history(game_counter, last_node->text, was_correct);

        if (is_multiplayer && current_player != NULL)
        {
            end_player_turn(current_player, was_correct);
            rotate_to_next_player();
        }
        game_counter++;
    }
    else
    {
        print_centered("Error: Tidak dapat memproses permainan!");
    }
    printf("\n");
    ready();
}

void handle_statistics_menu()
{
    int stats_choice;
    int continue_stats = 1;

    while (continue_stats)
    {
        stats_choice = get_menu_selection(6, print_statistics_menu);

        switch (stats_choice)
        {
        case 1:
            display_comprehensive_statistics();
            ready();
            break;
        case 2:
            display_game_history();
            ready();
            break;
        case 3:
            if (is_multiplayer || get_total_players() > 0)
            {
                display_player_rankings();
            }
            else
            {
                printf("Tidak ada data player untuk ranking.\n");
                printf("Mainkan mode multiplayer untuk melihat ranking.\n");
            }
            ready();
            break;
        case 4:
            display_question_suggestions();
            char *best_question = get_best_question_suggestion();
            if (best_question != NULL)
            {
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

void handle_admin_menu()
{
    int admin_choice;
    int continue_admin = 1;

    while (continue_admin)
    {
        admin_choice = get_menu_selection(7, print_admin_menu);
        switch (admin_choice)
        {
        case 1:
            iterative_preorder_traversal(root);
            ready();
            break;

        case 2:
            if (undo_last_operation(root))
            {
                printf("Menyimpan perubahan...\n");
                auto_save_tree(root);
            }
            else
            {
                printf("Tidak ada operasi yang dapat dibatalkan!\n");
            }
            ready();
            break;

        case 3:
            display_undo_history();
            ready();
            break;

        case 4:
            reset_all_data();
            free_tree(root);
            root = create_default_tree();
            if (root != NULL)
            {
                auto_save_tree(root);
                print_aligned_prompt("Database default berhasil dibuat ulang!");
                printf("\n");
            }
            game_counter = 1;
            ready();
            break;

        case 5:
            create_system_backup();
            ready();
            break;

        case 6:
            if (restore_system_backup())
            {
                // Reload tree from restored backup
                free_tree(root);
                if (load_or_create_database(&root) != 0)
                {
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

void display_game_info()
{
    printf("   INFORMASI GAME:\n");
    printf("   Game Counter: %d\n", game_counter);
    printf("   Mode: %s\n", is_multiplayer ? "Multiplayer" : "Single Player");
    printf("   Total Hewan: %d\n", count_total_animals(root));
    printf("   Success Rate: %.1f%%\n", get_success_rate());
    printf("\n");
}

void handle_emergency_save()
{
    printf("Menyimpan data darurat...\n");

    if (auto_save_tree(root) == 0)
    {
        printf("Tree berhasil disimpan!\n");
    }

    save_history_to_file();
    printf("History berhasil disimpan!\n");
}

// Signal handler for graceful shutdown (if needed)
void cleanup_on_exit()
{
    printf("\nProgram dihentikan! Menyimpan data...\n");
    handle_emergency_save();
    cleanup_system();
    free_tree(root);
    exit(0);
}
