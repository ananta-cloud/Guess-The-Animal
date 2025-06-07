#include "tree_operations.h"

/**
 * @brief Membuat pohon keputusan default yang sangat sederhana.
 * Hanya berisi satu pertanyaan dan dua hewan untuk memulai.
 * @return Pointer ke root dari pohon yang baru dibuat.
 */
TreeNodePtr create_default_tree() {
    // Alokasi memori untuk setiap node
    TreeNodePtr root = (TreeNodePtr)malloc(sizeof(TreeNode));
    TreeNodePtr yes_node = (TreeNodePtr)malloc(sizeof(TreeNode));
    TreeNodePtr no_node = (TreeNodePtr)malloc(sizeof(TreeNode));

    // Cek jika alokasi berhasil
    if (root == NULL || yes_node == NULL || no_node == NULL) {
        // Bebaskan memori yang sudah teralokasi jika terjadi kegagalan
        free(root);
        free(yes_node);
        free(no_node);
        return NULL;
    }

    // Mengatur pertanyaan root
    strcpy(root->text, "Apakah hewan ini hidup di darat?");
    root->yes_ans = yes_node;
    root->no_ans = no_node;

    // Mengatur jawaban untuk 'yes'
    strcpy(yes_node->text, "Kucing");
    yes_node->yes_ans = NULL;
    yes_node->no_ans = NULL;

    // Mengatur jawaban untuk 'no'
    strcpy(no_node->text, "Ikan");
    no_node->yes_ans = NULL;
    no_node->no_ans = NULL;

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
    char temp_input[MAX_TEXT_LENGTH + 10]; // Buffer sementara

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
