#include "tree_operations.h"

/**
 * @brief Membuat pohon keputusan default yang sangat sederhana.
 * Hanya berisi satu pertanyaan dan dua hewan untuk memulai.
 * @return Pointer ke root dari pohon yang baru dibuat.
 */
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

/**
 * @brief Membebaskan semua memori yang digunakan oleh pohon secara rekursif.
 * @param start Node awal untuk memulai pembebasan memori.
 */
void free_tree(TreeNodePtr start) {
    if (start != NULL) {
        free_tree(start->yes_ans);
        free_tree(start->no_ans);
        free(start);
    }
}

/**
 * @brief Menavigasi pohon berdasarkan jawaban pengguna (fungsi rekursif).
 * @param start Node saat ini.
 * @param last_accessed Pointer untuk menyimpan node jawaban terakhir yang dicapai.
 */
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

/**
 * @brief Mengajukan pertanyaan konfirmasi akhir kepada pengguna.
 * @param start Node yang berisi tebakan hewan.
 * @return 1 jika pengguna mengonfirmasi, 0 jika tidak.
 */
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

/**
 * @brief Memperluas pohon dengan menambahkan pertanyaan dan jawaban baru.
 * Ini adalah fungsi "belajar".
 * @param start Node tempat tebakan salah terjadi.
 */
void build_question(TreeNodePtr start) {
    char new_animal[MAX_TEXT_LENGTH];
    char new_question[MAX_TEXT_LENGTH];
    char temp_input[MAX_TEXT_LENGTH + 10];

    // Hewan lama (tebakan yang salah) akan menjadi jawaban 'no'
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

    // Alokasi node baru untuk jawaban 'yes' (hewan baru)
    TreeNodePtr yes_node = (TreeNodePtr)malloc(sizeof(TreeNode));
    strcpy(yes_node->text, new_animal);
    yes_node->yes_ans = NULL;
    yes_node->no_ans = NULL;

    // Alokasi node baru untuk jawaban 'no' (hewan lama)
    TreeNodePtr no_node = (TreeNodePtr)malloc(sizeof(TreeNode));
    strcpy(no_node->text, old_animal);
    no_node->yes_ans = NULL;
    no_node->no_ans = NULL;

    // Ubah node saat ini dari jawaban menjadi pertanyaan baru
    strcpy(start->text, new_question);
    start->yes_ans = yes_node;
    start->no_ans = no_node;
    
    printf("Terima kasih! Saya telah belajar sesuatu yang baru!\n");
}

/**
 * @brief Menulis struktur tree ke file (serialisasi) menggunakan pre-order traversal.
 * @param start Node awal.
 * @param out_file Pointer ke file yang dibuka untuk ditulis.
 */
void write_to_file(TreeNodePtr start, FILE* out_file) {
    if (start == NULL) {
        fprintf(out_file, "*\n"); // '*' menandakan node NULL
    } else {
        fprintf(out_file, "%s\n", start->text);
        write_to_file(start->yes_ans, out_file);
        write_to_file(start->no_ans, out_file);
    }
}

/**
 * @brief Membaca file dan membangun kembali struktur tree (deserialisasi).
 * @param start Pointer ke pointer node yang akan dibuat.
 * @param in_file Pointer ke file yang dibuka untuk dibaca.
 * @return 0 jika berhasil, 1 jika gagal.
 */
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

/**
 * @brief Fungsi pembungkus untuk menyimpan tree ke file default.
 * @param start Pointer ke root tree.
 * @return 0 jika berhasil, 1 jika gagal.
 */
int auto_save_tree(TreeNodePtr start) {
    FILE* out_file = fopen(DEFAULT_DB_FILE, "w");
    if (out_file == NULL) {
        return 1; // Gagal membuka file
    }
    
    write_to_file(start, out_file);
    fclose(out_file);
    
    return 0;
}

/**
 * @brief Memuat tree dari file jika ada, atau membuat tree default jika tidak ada.
 * @param head Pointer ke pointer root tree.
 * @return 0 jika berhasil, 1 jika gagal.
 */
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
