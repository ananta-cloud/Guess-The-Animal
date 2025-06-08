#include "tree_operations.h"
#include "stack_operations.h"

TreeNodePtr create_default_tree() {
    // Alokasi memori untuk semua node
    TreeNodePtr root = (TreeNodePtr)malloc(sizeof(TreeNode));
    
    // LEVEL 1: Tulang belakang (Vertebrata vs Invertebrata)
    TreeNodePtr vertebrata_node = (TreeNodePtr)malloc(sizeof(TreeNode));
    TreeNodePtr invertebrata_node = (TreeNodePtr)malloc(sizeof(TreeNode));
    
    // LEVEL 2: Habitat (Akuatik vs Darat) untuk Vertebrata
    TreeNodePtr vertebrata_water_node = (TreeNodePtr)malloc(sizeof(TreeNode));
    TreeNodePtr vertebrata_land_node = (TreeNodePtr)malloc(sizeof(TreeNode));
    
    // LEVEL 2: Habitat (Akuatik vs Darat) untuk Invertebrata
    TreeNodePtr invertebrata_water_node = (TreeNodePtr)malloc(sizeof(TreeNode));
    TreeNodePtr invertebrata_land_node = (TreeNodePtr)malloc(sizeof(TreeNode));
    
    // LEVEL 3: Vertebrata Air - Bernapas dengan insang?
    TreeNodePtr vertebrata_water_gills_node = (TreeNodePtr)malloc(sizeof(TreeNode));
    TreeNodePtr vertebrata_water_nogills_node = (TreeNodePtr)malloc(sizeof(TreeNode));
    
    // LEVEL 3: Vertebrata Darat - Menyusui anaknya?
    TreeNodePtr vertebrata_land_mammal_node = (TreeNodePtr)malloc(sizeof(TreeNode));
    TreeNodePtr vertebrata_land_nomammal_node = (TreeNodePtr)malloc(sizeof(TreeNode));
    
    // LEVEL 3: Invertebrata Air - Memiliki cangkang?
    TreeNodePtr invertebrata_water_shell_node = (TreeNodePtr)malloc(sizeof(TreeNode));
    TreeNodePtr invertebrata_water_noshell_node = (TreeNodePtr)malloc(sizeof(TreeNode));
    
    // LEVEL 3: Invertebrata Darat - Dapat terbang?
    TreeNodePtr invertebrata_land_fly_node = (TreeNodePtr)malloc(sizeof(TreeNode));
    TreeNodePtr invertebrata_land_nofly_node = (TreeNodePtr)malloc(sizeof(TreeNode));
    
    // LEVEL 4: Vertebrata Air dengan Insang - Predator?
    TreeNodePtr fish_predator_node = (TreeNodePtr)malloc(sizeof(TreeNode));
    TreeNodePtr fish_peaceful_node = (TreeNodePtr)malloc(sizeof(TreeNode));
    
    // LEVEL 4: Vertebrata Air tanpa Insang - Menyusui?
    TreeNodePtr aquatic_mammal_node = (TreeNodePtr)malloc(sizeof(TreeNode));
    TreeNodePtr amphibian_node = (TreeNodePtr)malloc(sizeof(TreeNode));
    
    // LEVEL 4: Vertebrata Darat Mamalia - Berukuran besar?
    TreeNodePtr mammal_large_node = (TreeNodePtr)malloc(sizeof(TreeNode));
    TreeNodePtr mammal_small_node = (TreeNodePtr)malloc(sizeof(TreeNode));
    
    // LEVEL 4: Vertebrata Darat Non-Mamalia - Bertelur dan punya sayap?
    TreeNodePtr bird_node = (TreeNodePtr)malloc(sizeof(TreeNode));
    TreeNodePtr reptile_node = (TreeNodePtr)malloc(sizeof(TreeNode));
    
    // LEVEL 4: Invertebrata Air dengan Cangkang - Banyak kaki?
    TreeNodePtr crustacean_node = (TreeNodePtr)malloc(sizeof(TreeNode));
    TreeNodePtr mollusk_shell_node = (TreeNodePtr)malloc(sizeof(TreeNode));
    
    // LEVEL 4: Invertebrata Air tanpa Cangkang - Bertentakel?
    TreeNodePtr tentacle_node = (TreeNodePtr)malloc(sizeof(TreeNode));
    TreeNodePtr jellyfish_node = (TreeNodePtr)malloc(sizeof(TreeNode));
    
    // LEVEL 4: Invertebrata Darat Terbang - Tubuh berwarna cerah?
    TreeNodePtr colorful_insect_node = (TreeNodePtr)malloc(sizeof(TreeNode));
    TreeNodePtr plain_insect_node = (TreeNodePtr)malloc(sizeof(TreeNode));
    
    // LEVEL 4: Invertebrata Darat Tidak Terbang - Kaki delapan?
    TreeNodePtr eight_legs_node = (TreeNodePtr)malloc(sizeof(TreeNode));
    TreeNodePtr no_legs_node = (TreeNodePtr)malloc(sizeof(TreeNode));
    
    // Final answer nodes - hewan spesifik
    // Vertebrata Air
    TreeNodePtr shark_node = (TreeNodePtr)malloc(sizeof(TreeNode));
    TreeNodePtr goldfish_node = (TreeNodePtr)malloc(sizeof(TreeNode));
    TreeNodePtr whale_node = (TreeNodePtr)malloc(sizeof(TreeNode));
    TreeNodePtr frog_node = (TreeNodePtr)malloc(sizeof(TreeNode));
    
    // Vertebrata Darat
    TreeNodePtr cow_node = (TreeNodePtr)malloc(sizeof(TreeNode));
    TreeNodePtr cat_node = (TreeNodePtr)malloc(sizeof(TreeNode));
    TreeNodePtr chicken_node = (TreeNodePtr)malloc(sizeof(TreeNode));
    TreeNodePtr snake_node = (TreeNodePtr)malloc(sizeof(TreeNode));
    
    // Invertebrata Air
    TreeNodePtr crab_node = (TreeNodePtr)malloc(sizeof(TreeNode));
    TreeNodePtr snail_node = (TreeNodePtr)malloc(sizeof(TreeNode));
    TreeNodePtr octopus_node = (TreeNodePtr)malloc(sizeof(TreeNode));
    TreeNodePtr jellyfish_final_node = (TreeNodePtr)malloc(sizeof(TreeNode));
    
    // Invertebrata Darat
    TreeNodePtr butterfly_node = (TreeNodePtr)malloc(sizeof(TreeNode));
    TreeNodePtr ant_node = (TreeNodePtr)malloc(sizeof(TreeNode));
    TreeNodePtr spider_node = (TreeNodePtr)malloc(sizeof(TreeNode));
    TreeNodePtr worm_node = (TreeNodePtr)malloc(sizeof(TreeNode));
    
    // Array untuk error checking
    TreeNodePtr nodes[] = {
        root, vertebrata_node, invertebrata_node, vertebrata_water_node, vertebrata_land_node,
        invertebrata_water_node, invertebrata_land_node, vertebrata_water_gills_node, 
        vertebrata_water_nogills_node, vertebrata_land_mammal_node, vertebrata_land_nomammal_node,
        invertebrata_water_shell_node, invertebrata_water_noshell_node, invertebrata_land_fly_node,
        invertebrata_land_nofly_node, fish_predator_node, fish_peaceful_node, aquatic_mammal_node,
        amphibian_node, mammal_large_node, mammal_small_node, bird_node, reptile_node,
        crustacean_node, mollusk_shell_node, tentacle_node, jellyfish_node, colorful_insect_node,
        plain_insect_node, eight_legs_node, no_legs_node,
        shark_node, goldfish_node, whale_node, frog_node, cow_node, cat_node, chicken_node,
        snake_node, crab_node, snail_node, octopus_node, jellyfish_final_node, butterfly_node,
        ant_node, spider_node, worm_node
    };
    
    int total_nodes = sizeof(nodes) / sizeof(nodes[0]);
    
    // Error checking
    for (int i = 0; i < total_nodes; i++) {
        if (nodes[i] == NULL) {
            for (int j = 0; j < i; j++) {
                if (nodes[j]) free(nodes[j]);
            }
            return NULL;
        }
    }
    
    // === STRUKTUR POHON KEPUTUSAN BERDASARKAN KLASIFIKASI ILMIAH ===
    
    // LEVEL 1: Pertanyaan fundamental tentang tulang belakang
    strcpy(root->text, "Apakah hewan ini memiliki tulang belakang?");
    root->yes_ans = vertebrata_node;
    root->no_ans = invertebrata_node;
    
    // LEVEL 2a: Vertebrata - Habitat utama
    strcpy(vertebrata_node->text, "Apakah hewan ini hidup di dalam air (seluruhnya atau sebagian besar waktunya)?");
    vertebrata_node->yes_ans = vertebrata_water_node;
    vertebrata_node->no_ans = vertebrata_land_node;
    
    // LEVEL 2b: Invertebrata - Habitat utama
    strcpy(invertebrata_node->text, "Apakah hewan ini hidup di dalam air (seluruhnya atau sebagian besar waktunya)?");
    invertebrata_node->yes_ans = invertebrata_water_node;
    invertebrata_node->no_ans = invertebrata_land_node;
    
    // LEVEL 3a: Vertebrata Air - Sistem pernapasan
    strcpy(vertebrata_water_node->text, "Apakah hewan ini bernapas dengan insang?");
    vertebrata_water_node->yes_ans = vertebrata_water_gills_node;
    vertebrata_water_node->no_ans = vertebrata_water_nogills_node;
    
    // LEVEL 3b: Vertebrata Darat - Sistem reproduksi
    strcpy(vertebrata_land_node->text, "Apakah hewan ini menyusui anaknya?");
    vertebrata_land_node->yes_ans = vertebrata_land_mammal_node;
    vertebrata_land_node->no_ans = vertebrata_land_nomammal_node;
    
    // LEVEL 3c: Invertebrata Air - Struktur pelindung
    strcpy(invertebrata_water_node->text, "Apakah hewan ini memiliki cangkang keras?");
    invertebrata_water_node->yes_ans = invertebrata_water_shell_node;
    invertebrata_water_node->no_ans = invertebrata_water_noshell_node;
    
    // LEVEL 3d: Invertebrata Darat - Kemampuan terbang
    strcpy(invertebrata_land_node->text, "Apakah hewan ini dapat terbang (memiliki sayap)?");
    invertebrata_land_node->yes_ans = invertebrata_land_fly_node;
    invertebrata_land_node->no_ans = invertebrata_land_nofly_node;
    
    // LEVEL 4a: Ikan (Vertebrata Air dengan Insang) - Sifat predator
    strcpy(vertebrata_water_gills_node->text, "Apakah hewan ini adalah predator berbahaya dengan gigi tajam?");
    vertebrata_water_gills_node->yes_ans = fish_predator_node;
    vertebrata_water_gills_node->no_ans = fish_peaceful_node;
    
    // LEVEL 4b: Vertebrata Air tanpa Insang - Menyusui atau tidak
    strcpy(vertebrata_water_nogills_node->text, "Apakah hewan ini menyusui anaknya?");
    vertebrata_water_nogills_node->yes_ans = aquatic_mammal_node;
    vertebrata_water_nogills_node->no_ans = amphibian_node;
    
    // LEVEL 4c: Mamalia Darat - Ukuran tubuh
    strcpy(vertebrata_land_mammal_node->text, "Apakah hewan ini berukuran besar (lebih besar dari anjing)?");
    vertebrata_land_mammal_node->yes_ans = mammal_large_node;
    vertebrata_land_mammal_node->no_ans = mammal_small_node;
    
    // LEVEL 4d: Vertebrata Darat Non-Mamalia - Kemampuan terbang
    strcpy(vertebrata_land_nomammal_node->text, "Apakah hewan ini bertelur dan memiliki sayap untuk terbang?");
    vertebrata_land_nomammal_node->yes_ans = bird_node;
    vertebrata_land_nomammal_node->no_ans = reptile_node;
    
    // LEVEL 4e: Invertebrata Air dengan Cangkang - Jumlah kaki
    strcpy(invertebrata_water_shell_node->text, "Apakah hewan ini memiliki banyak kaki untuk berjalan?");
    invertebrata_water_shell_node->yes_ans = crustacean_node;
    invertebrata_water_shell_node->no_ans = mollusk_shell_node;
    
    // LEVEL 4f: Invertebrata Air tanpa Cangkang - Tentakel
    strcpy(invertebrata_water_noshell_node->text, "Apakah hewan ini memiliki tentakel panjang?");
    invertebrata_water_noshell_node->yes_ans = tentacle_node;
    invertebrata_water_noshell_node->no_ans = jellyfish_node;
    
    // LEVEL 4g: Serangga Terbang - Warna tubuh
    strcpy(invertebrata_land_fly_node->text, "Apakah hewan ini memiliki tubuh dan sayap berwarna cerah?");
    invertebrata_land_fly_node->yes_ans = colorful_insect_node;
    invertebrata_land_fly_node->no_ans = plain_insect_node;
    
    // LEVEL 4h: Invertebrata Darat Tidak Terbang - Jumlah kaki
    strcpy(invertebrata_land_nofly_node->text, "Apakah hewan ini memiliki delapan kaki?");
    invertebrata_land_nofly_node->yes_ans = eight_legs_node;
    invertebrata_land_nofly_node->no_ans = no_legs_node;
    
    // === PERTANYAAN FINAL UNTUK MENENTUKAN HEWAN SPESIFIK ===
    
    // Ikan predator vs ikan damai
    strcpy(fish_predator_node->text, "Hiu");
    fish_predator_node->yes_ans = NULL;
    fish_predator_node->no_ans = NULL;
    
    strcpy(fish_peaceful_node->text, "Ikan Mas");
    fish_peaceful_node->yes_ans = NULL;
    fish_peaceful_node->no_ans = NULL;
    
    // Mamalia air vs amfibi
    strcpy(aquatic_mammal_node->text, "Paus");
    aquatic_mammal_node->yes_ans = NULL;
    aquatic_mammal_node->no_ans = NULL;
    
    strcpy(amphibian_node->text, "Kodok");
    amphibian_node->yes_ans = NULL;
    amphibian_node->no_ans = NULL;
    
    // Mamalia besar vs kecil
    strcpy(mammal_large_node->text, "Sapi");
    mammal_large_node->yes_ans = NULL;
    mammal_large_node->no_ans = NULL;
    
    strcpy(mammal_small_node->text, "Kucing");
    mammal_small_node->yes_ans = NULL;
    mammal_small_node->no_ans = NULL;
    
    // Burung vs reptil
    strcpy(bird_node->text, "Ayam");
    bird_node->yes_ans = NULL;
    bird_node->no_ans = NULL;
    
    strcpy(reptile_node->text, "Ular");
    reptile_node->yes_ans = NULL;
    reptile_node->no_ans = NULL;
    
    // Krustasea vs moluska bercangkang
    strcpy(crustacean_node->text, "Kepiting");
    crustacean_node->yes_ans = NULL;
    crustacean_node->no_ans = NULL;
    
    strcpy(mollusk_shell_node->text, "Siput");
    mollusk_shell_node->yes_ans = NULL;
    mollusk_shell_node->no_ans = NULL;
    
    // Hewan bertentakel vs ubur-ubur
    strcpy(tentacle_node->text, "Gurita");
    tentacle_node->yes_ans = NULL;
    tentacle_node->no_ans = NULL;
    
    strcpy(jellyfish_node->text, "Ubur-ubur");
    jellyfish_node->yes_ans = NULL;
    jellyfish_node->no_ans = NULL;
    
    // Serangga berwarna vs polos
    strcpy(colorful_insect_node->text, "Kupu-kupu");
    colorful_insect_node->yes_ans = NULL;
    colorful_insect_node->no_ans = NULL;
    
    strcpy(plain_insect_node->text, "Semut");
    plain_insect_node->yes_ans = NULL;
    plain_insect_node->no_ans = NULL;
    
    // Laba-laba vs cacing
    strcpy(eight_legs_node->text, "Laba-laba");
    eight_legs_node->yes_ans = NULL;
    eight_legs_node->no_ans = NULL;
    
    strcpy(no_legs_node->text, "Cacing");
    no_legs_node->yes_ans = NULL;
    no_legs_node->no_ans = NULL;
    
    return root;
}

void free_tree(TreeNodePtr start) {
    if (start != NULL) {
        free_tree(start->yes_ans);
        free_tree(start->no_ans);
        free(start);
    }
}

TreeNodePtr copy_node(TreeNodePtr original) {
    if (original == NULL) return NULL;
    
    TreeNodePtr copy = (TreeNodePtr)malloc(sizeof(TreeNode));
    if (copy == NULL) return NULL;
    
    strcpy(copy->text, original->text);
    copy->yes_ans = original->yes_ans;
    copy->no_ans = original->no_ans;
    
    return copy;
}

void write_to_file(TreeNodePtr start, FILE* out_file) {
    if (start == NULL) {
        fprintf(out_file, "*\n");
    } else {
        fprintf(out_file, "%s\n", start->text);
        write_to_file(start->yes_ans, out_file);
        write_to_file(start->no_ans, out_file);
    }
}

int read_from_file(TreeNodePtr* start, FILE* in_file) {
    char input[MAX_TEXT_LENGTH + 10];
    
    if (fgets(input, sizeof(input), in_file) == NULL) {
        *start = NULL;
        return 1;
    }
    
    trim_string(input);
    
    if (strcmp(input, "*") != 0) {
        *start = (TreeNodePtr)malloc(sizeof(TreeNode));
        if (*start == NULL) {
            return 1;
        }
        
        strcpy((*start)->text, input);
      
        if (read_from_file(&((*start)->yes_ans), in_file) != 0 ||
            read_from_file(&((*start)->no_ans), in_file) != 0) {
            free(*start);
            *start = NULL;
            return 1;
        }
    } else {
        *start = NULL;
    }
    
    return 0;
}

int auto_save_tree(TreeNodePtr start) {
    create_backup();
    
    FILE* out_file = fopen(DEFAULT_DB_FILE, "w");
    if (out_file == NULL) {
        return 1;
    }
    
    write_to_file(start, out_file);
    fclose(out_file);
    
    return 0;
}

int create_backup() {
    FILE* source = fopen(DEFAULT_DB_FILE, "r");
    FILE* dest = fopen(BACKUP_DB_FILE, "w");
    
    if (source == NULL || dest == NULL) {
        if (source) fclose(source);
        if (dest) fclose(dest);
        return 1;
    }
    
    char buffer[1024];
    size_t bytes;
    
    while ((bytes = fread(buffer, 1, sizeof(buffer), source)) > 0) {
        fwrite(buffer, 1, bytes, dest);
    }
    
    fclose(source);
    fclose(dest);
    return 0;
}

int load_or_create_database(TreeNodePtr* head) {
    FILE* in_file = fopen(DEFAULT_DB_FILE, "r");
    
    if (in_file != NULL) {
        printf("Memuat database yang sudah ada...\n");
        if (read_from_file(head, in_file) == 0) {
            printf("Database berhasil dimuat!\n");
            fclose(in_file);
            return 0;
        } else {
            printf("Database rusak, membuat database baru...\n");
            fclose(in_file);
        }
    } else {
        printf("Database tidak ditemukan, membuat database baru...\n");
    }
    
    *head = create_default_tree();
    if (*head == NULL) {
        return 1;
    }
    
    if (auto_save_tree(*head) == 0) {
        printf("Database baru berhasil dibuat!\n");
    }
    
    return 0;
}

void choice(TreeNodePtr start, TreeNodePtr* last_accessed) {
    int user_choice;
    
    *last_accessed = start;
    
    if (start->yes_ans == NULL && start->no_ans == NULL) {
        return;
    }
    
    while (1) {
        printf("%s ", start->text);
        user_choice = get_answer();
        
        if (user_choice == 0) {
            choice(start->no_ans, last_accessed);
            break;
        } else if (user_choice == 1) {
            choice(start->yes_ans, last_accessed);
            break;
        } else {
            printf("Jawaban tidak valid. Silakan jawab 'yes' atau 'no'.\n");
        }
    }
}

int ask_if_animal(TreeNodePtr start) {
    int user_decision;
    
    while (1) {
        printf("Apakah hewan Anda adalah: %s? ", start->text);
        user_decision = get_answer();
        
        if (user_decision == 0) {
            return 0;
        } else if (user_decision == 1) {
            return 1;
        } else {
            printf("Jawaban tidak valid. Silakan jawab 'yes' atau 'no'.\n");
        }
    }
}

void build_question(TreeNodePtr start) {
    char new_animal[MAX_TEXT_LENGTH];
    char new_question[MAX_TEXT_LENGTH];
    char temp_input[MAX_TEXT_LENGTH + 10];
    
    // Save current state for undo functionality
    save_current_state_before_learning(start);
    
    printf("Hewan apa yang Anda pikirkan? ");
    if (fgets(temp_input, sizeof(temp_input), stdin) != NULL) {
        strncpy(new_animal, temp_input, MAX_TEXT_LENGTH - 1);
        new_animal[MAX_TEXT_LENGTH - 1] = '\0';
        trim_string(new_animal);
    } else {
        strcpy(new_animal, "Hewan Tidak Diketahui");
    }
    
    printf("\nBantu saya belajar! Buatlah pertanyaan yang membedakan:\n");
    printf("   - Jawaban 'YES' untuk: %s\n", new_animal);
    printf("   - Jawaban 'NO' untuk: %s\n", start->text);
    printf("\nPertanyaan Anda: ");
    
    if (fgets(temp_input, sizeof(temp_input), stdin) != NULL) {
        strncpy(new_question, temp_input, MAX_TEXT_LENGTH - 1);
        new_question[MAX_TEXT_LENGTH - 1] = '\0';
        trim_string(new_question);
    } else {
        snprintf(new_question, MAX_TEXT_LENGTH, "Apakah ini %s?", new_animal);
    }
    
    TreeNodePtr yes_node = (TreeNodePtr)malloc(sizeof(TreeNode));
    if (yes_node == NULL) {
        printf("Error: Tidak cukup memory!\n");
        return;
    }
    strcpy(yes_node->text, new_animal);
    yes_node->yes_ans = NULL;
    yes_node->no_ans = NULL;
    
    TreeNodePtr no_node = (TreeNodePtr)malloc(sizeof(TreeNode));
    if (no_node == NULL) {
        printf("Error: Tidak cukup memory!\n");
        free(yes_node);
        return;
    }
    strcpy(no_node->text, start->text);
    no_node->yes_ans = start->yes_ans;
    no_node->no_ans = start->no_ans;
    
    strcpy(start->text, new_question);
    start->yes_ans = yes_node;
    start->no_ans = no_node;
    
    printf("Terima kasih! Saya telah belajar sesuatu yang baru!\n");
    printf("Tips: Anda dapat membatalkan pembelajaran ini dengan fitur 'Undo'\n");
}

int count_total_animals(TreeNodePtr root) {
    if (root == NULL) return 0;
    
    if (root->yes_ans == NULL && root->no_ans == NULL) {
        return 1; // Leaf node (animal)
    }
    
    return count_total_animals(root->yes_ans) + count_total_animals(root->no_ans);
}

int calculate_tree_depth(TreeNodePtr root) {
    if (root == NULL) return 0;
    
    int left_depth = calculate_tree_depth(root->yes_ans);
    int right_depth = calculate_tree_depth(root->no_ans);
    
    return 1 + (left_depth > right_depth ? left_depth : right_depth);
}

void display_all_animals(TreeNodePtr root) {
    if (root == NULL) return;
    
    if (root->yes_ans == NULL && root->no_ans == NULL) {
        printf("%s\n", root->text);
        return;
    }
    
    display_all_animals(root->yes_ans);
    display_all_animals(root->no_ans);
}

void iterative_preorder_traversal(TreeNodePtr root) {
    if (root == NULL) return;
    
    TreeStack* stack = NULL;
    push_tree_node(&stack, root);
    
    printf("\n=== Tree Structure (Pre-order) ===\n");
    int level = 0;
    
    while (!is_tree_stack_empty(stack)) {
        TreeNodePtr current = pop_tree_node(&stack);
        
        // Print with indentation based on level
        for (int i = 0; i < level; i++) printf("  ");
        
        if (current->yes_ans == NULL && current->no_ans == NULL) {
            printf("Animal: %s\n", current->text);
        } else {
            printf("Question: %s\n", current->text);
        }
        
        // Push right child first, then left child (for correct order)
        if (current->no_ans) push_tree_node(&stack, current->no_ans);
        if (current->yes_ans) push_tree_node(&stack, current->yes_ans);
        
        level++;
    }
    
    clear_tree_stack(&stack);
}