#include "tree_operations.h"
#include "stack_operations.h"

// Untuk Membuat Tree pertnayaan sederhana
TreeNodePtr create_default_tree() {
    // Alokasi memori untuk setiap node
    TreeNodePtr root = (TreeNodePtr)malloc(sizeof(TreeNode));
    TreeNodePtr vertebrata_node = (TreeNodePtr)malloc(sizeof(TreeNode));
    TreeNodePtr invertebrata_node = (TreeNodePtr)malloc(sizeof(TreeNode));
    TreeNodePtr kucing_node = (TreeNodePtr)malloc(sizeof(TreeNode));
    TreeNodePtr ular_node = (TreeNodePtr)malloc(sizeof(TreeNode));

    strcpy(root->text, "Apakah hewan ini memiliki tulang belakang?");
    root->yes_ans = vertebrata_node;
    root->no_ans = invertebrata_node;

    strcpy(vertebrata_node->text, "Apakah hewan ini menyusui?");
    vertebrata_node->yes_ans = kucing_node;
    vertebrata_node->no_ans = ular_node;

    strcpy(invertebrata_node->text, "Cacing");
    invertebrata_node->yes_ans = NULL;
    invertebrata_node->no_ans = NULL;

    strcpy(kucing_node->text, "Kucing");
    kucing_node->yes_ans = NULL;
    kucing_node->no_ans = NULL;

    strcpy(ular_node->text, "Ular");
    ular_node->yes_ans = NULL;
    ular_node->no_ans = NULL;

    return root;
}

// Dealokalisasi tree
void free_tree(TreeNodePtr start) {
    if (start != NULL) {
        free_tree(start->yes_ans);
        free_tree(start->no_ans);
        free(start);
    }
}

// Menulis struktur tree ke file (serialisasi) menggunakan pre-order traversal
void write_to_file(TreeNodePtr start, FILE* out_file) {
    if (start == NULL) {
        fprintf(out_file, "*\n"); // '*' menandakan node NULL
    } else {
        fprintf(out_file, "%s\n", start->text);
        write_to_file(start->yes_ans, out_file);
        write_to_file(start->no_ans, out_file);
    }
}

// Membaca file dan membangun kembali struktur tree (deserialisasi)
int read_from_file(TreeNodePtr* start, FILE* in_file) {
    char input[MAX_TEXT_LENGTH + 10];
    
    if (fgets(input, sizeof(input), in_file) == NULL) {
        *start = NULL;
        return 1; // Gagal membaca file
    }
    trim_string(input);
    
    if (strcmp(input, "*") != 0) {
        *start = (TreeNodePtr)malloc(sizeof(TreeNode));
        if (*start == NULL) return 1; // Gagal alokasi memori
        
        strcpy((*start)->text, input);
      
        if (read_from_file(&((*start)->yes_ans), in_file) != 0 ||
            read_from_file(&((*start)->no_ans), in_file) != 0) {
            free(*start);
            *start = NULL;
            return 1; // Gagal membaca sub-tree
        }
    } else {
        *start = NULL; // Node ini adalah NULL
    }
    
    return 0; // Sukses
}

// Fungsi pembungkus untuk menyimpan tree ke file default
int auto_save_tree(TreeNodePtr start) {
    FILE* out_file = fopen(DEFAULT_DB_FILE, "w");
    if (out_file == NULL) {
        return 1; // Gagal membuka file
    }
    
    write_to_file(start, out_file);
    fclose(out_file);
    
    return 0;
}

int load_or_create_database(TreeNodePtr* head) {
    FILE* in_file = fopen(DEFAULT_DB_FILE, "r");
    
    if (in_file != NULL) { // Jika file database ada
        printf("Memuat database yang sudah ada...\n");
        if (read_from_file(head, in_file) == 0) {
            printf("Database berhasil dimuat!\n");
            fclose(in_file);
            return 0; // Sukses memuat
        } else {
            printf("Database rusak, membuat database baru...\n");
            fclose(in_file);
        }
    } else { // Jika file tidak ditemukan
        printf("Database tidak ditemukan, membuat database baru...\n");
    }
    
    // Buat database default jika gagal memuat atau file tidak ada
    *head = create_default_tree();
    if (*head == NULL) return 1; // Gagal membuat tree
    
    if (auto_save_tree(*head) == 0) {
        printf("Database baru berhasil dibuat dan disimpan!\n");
    }
    
    return 0;
}

// Navigasi pergerakan Tree tergantung jawaban 'Yes' or 'No' pengguna
void choice(TreeNodePtr start, TreeNodePtr* last_accessed) {
    *last_accessed = start; // Simpan node saat ini sebagai yang terakhir diakses

    // Jika ini adalah node daun (jawaban), hentikan rekursi.
    if (start->yes_ans == NULL && start->no_ans == NULL) {
        return;
    }

    int user_choice;
    while (1) {
        printf("%s (yes/no): ", start->text);
        user_choice = get_answer();

        if (user_choice == 0) { // Jawaban 'no'
            choice(start->no_ans, last_accessed);
            break;
        } else if (user_choice == 1) { // Jawaban 'yes'
            choice(start->yes_ans, last_accessed);
            break;
        } else {
            printf("Jawaban tidak valid. Silakan jawab 'yes' atau 'no'.\n");
        }
    }
}

// Mengajukan pertanyaan konfirmasi akhir kepada pengguna.
int ask_if_animal(TreeNodePtr start) {
    int user_decision;
    while (1) {
        printf("Apakah hewan Anda adalah: %s? (yes/no): ", start->text);
        user_decision = get_answer();

        if (user_decision == 0) {
            return 0; // Pengguna menjawab 'no'
        } else if (user_decision == 1) {
            return 1; // Pengguna menjawab 'yes'
        } else {
            printf("Jawaban tidak valid. Silakan jawab 'yes' atau 'no'.\n");
        }
    }
}

void build_question(TreeNodePtr start) {
    char new_animal[MAX_TEXT_LENGTH], new_question[MAX_TEXT_LENGTH], temp_input[MAX_TEXT_LENGTH + 10];
    save_current_state_before_learning(start);
    
    char old_animal[MAX_TEXT_LENGTH];
    strcpy(old_animal, start->text);

    printf("Saya menyerah. Hewan apa yang Anda pikirkan? ");
    fgets(temp_input, sizeof(temp_input), stdin);
    trim_string(temp_input);
    strcpy(new_animal, temp_input);

    printf("Tolong berikan pertanyaan yang jawabannya 'yes' untuk %s dan 'no' untuk %s:\n", new_animal, old_animal);
    printf("Pertanyaan: ");
    fgets(temp_input, sizeof(temp_input), stdin);
    trim_string(temp_input);
    strcpy(new_question, temp_input);

    TreeNodePtr yes_node = (TreeNodePtr)malloc(sizeof(TreeNode));
    strcpy(yes_node->text, new_animal);
    yes_node->yes_ans = NULL;
    yes_node->no_ans = NULL;

    TreeNodePtr no_node = (TreeNodePtr)malloc(sizeof(TreeNode));
    strcpy(no_node->text, old_animal);
    no_node->yes_ans = start->yes_ans; // Pertahankan sub-tree lama jika ada
    no_node->no_ans = start->no_ans;

    strcpy(start->text, new_question);
    start->yes_ans = yes_node;
    start->no_ans = no_node;
    
    printf("Terima kasih! Saya telah belajar sesuatu yang baru!\n");
    printf("Tips: Anda dapat membatalkan pembelajaran ini melalui Menu Admin.\n");
}