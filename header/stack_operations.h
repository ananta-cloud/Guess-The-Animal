#ifndef STACK_OPERATIONS_H
#define STACK_OPERATIONS_H

#include "common_types.h"

// Operasi stack untuk fungsionalitas undo

/*
 * Mendorong (push) keadaan sebuah node ke tumpukan undo sebelum diubah.
 * IS: Tumpukan berisi n state, node akan dimodifikasi.
 * FS: Tumpukan berisi n+1 state, dengan state node yang baru disimpan di puncak.
 */
void push_undo_state(TreeNodePtr node, const char* original_text, 
                     TreeNodePtr original_yes, TreeNodePtr original_no, 
                     const char* operation_type);

/*
 * Mengambil (pop) keadaan terakhir dari tumpukan undo.
 * IS: Tumpukan berisi n state (n > 0).
 * FS: Tumpukan berisi n-1 state, dan data state teratas dikembalikan melalui parameter.
 */
int pop_undo_state(TreeNodePtr* node, char* original_text, 
                   TreeNodePtr* original_yes, TreeNodePtr* original_no, 
                   char* operation_type);

/*
 * Menjalankan operasi undo terakhir, mengembalikan node ke keadaan sebelumnya.
 * IS: Pohon telah dimodifikasi dan tumpukan undo tidak kosong.
 * FS: Modifikasi terakhir pada pohon dibatalkan, pohon kembali ke keadaan sebelum perubahan.
 */
int undo_last_operation(TreeNodePtr root);

/*
 * Menghapus semua data dari tumpukan undo dan membebaskan memori.
 * IS: Tumpukan undo berisi n state.
 * FS: Tumpukan undo menjadi kosong.
 */
void clear_undo_stack();

/*
 * Memeriksa apakah tumpukan undo kosong.
 * IS: Tumpukan undo ada di memori.
 * FS: Mengembalikan 1 jika kosong, 0 jika berisi data.
 */
int is_undo_stack_empty();

/*
 * Mendapatkan jumlah operasi yang dapat di-undo.
 * IS: Tumpukan undo berisi n state.
 * FS: Mengembalikan nilai n.
 */
int get_undo_stack_size();

/*
 * Menampilkan riwayat operasi yang tersimpan di tumpukan undo.
 * IS: Tumpukan undo berisi data operasi.
 * FS: Daftar riwayat undo tercetak di layar.
 */
void display_undo_history();

/*
 * Melihat state di puncak tumpukan undo tanpa menghapusnya.
 * IS: Tumpukan undo berisi n state.
 * FS: Mengembalikan pointer ke state teratas.
 */
UndoStack* peek_undo_stack();

/*
 * Fungsi pembungkus untuk menyimpan keadaan node sebelum proses belajar.
 * IS: Node akan dimodifikasi oleh fungsi build_question.
 * FS: Keadaan node saat ini telah disimpan ke tumpukan undo.
 */
void save_current_state_before_learning(TreeNodePtr node);

// Struct untuk traversal tree
typedef struct TreeStack {
    TreeNodePtr node;
    int level;
    struct TreeStack* next;
} TreeStack;

/*
 * Mendorong (push) node pohon ke tumpukan traversal.
 * IS: Tumpukan berisi n node.
 * FS: Tumpukan berisi n+1 node.
 */
void push_tree_node(TreeStack** stack, TreeNodePtr node, int level);

/*
 * Mengambil (pop) node pohon dari tumpukan traversal.
 * IS: Tumpukan berisi n node (n > 0).
 * FS: Tumpukan berisi n-1 node, dan node teratas dikembalikan.
 */
TreeNodePtr pop_tree_node(TreeStack** stack, int* level_out);

/*
 * Memeriksa apakah tumpukan traversal pohon kosong.
 * IS: Tumpukan traversal ada di memori.
 * FS: Mengembalikan 1 jika kosong, 0 jika berisi node.
 */
int is_tree_stack_empty(TreeStack* stack);

/*
 * Menghapus semua data dari tumpukan traversal pohon.
 * IS: Tumpukan traversal berisi n node.
 * FS: Tumpukan traversal menjadi kosong.
 */
void clear_tree_stack(TreeStack** stack);

#endif // STACK_OPERATIONS_H