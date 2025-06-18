#ifndef TREE_OPERATIONS_H
#define TREE_OPERATIONS_H

#include "common_types.h"

// Tree management functions

/*
 * Membuat struktur pohon pengetahuan default yang berisi beberapa hewan dan pertanyaan dasar.
 * IS: Belum ada pohon di memori.
 * FS: Mengembalikan pointer ke root dari pohon default yang baru dibuat.
 */
TreeNodePtr create_default_tree();

/*
 * Membebaskan semua memori yang dialokasikan untuk pohon.
 * IS: Pohon dan semua nodenya ada di memori.
 * FS: Semua memori yang digunakan oleh pohon telah dibebaskan.
 */
void free_tree(TreeNodePtr start);

/*
 * Membuat salinan dari sebuah node pohon.
 * IS: Node asli ada di memori.
 * FS: Mengembalikan pointer ke node baru yang merupakan salinan dari node asli.
 */
TreeNodePtr copy_node(TreeNodePtr original);

// File I/O operations

/*
 * Menulis struktur pohon ke file teks dengan format pre-order.
 * IS: Pohon ada di memori dan file tujuan terbuka untuk ditulis.
 * FS: File berisi representasi teks dari seluruh struktur pohon.
 */
void write_to_file(TreeNodePtr start, FILE* out_file);

/*
 * Membaca data dari file teks dan membangun kembali struktur pohon di memori.
 * IS: File berisi data pohon dan pointer root kosong.
 * FS: Pointer root menunjuk ke pohon yang telah dimuat dari file.
 */
int read_from_file(TreeNodePtr* start, FILE* in_file);

/*
 * Menyimpan struktur pohon saat ini secara otomatis ke file database default.
 * IS: Pohon di memori mungkin telah berubah.
 * FS: File `animal_database.txt` diperbarui dengan struktur pohon saat ini.
 */
int auto_save_tree(TreeNodePtr start);

/*
 * Membuat salinan cadangan dari file database utama.
 * IS: File `animal_database.txt` ada.
 * FS: File `animal_database_backup.txt` dibuat/diperbarui dengan isi dari database utama.
 */
int create_backup();

/*
 * Memuat database dari file jika ada, atau membuat database baru jika tidak ditemukan.
 * IS: Pointer root pohon masih kosong (NULL).
 * FS: Pointer root menunjuk ke pohon yang berhasil dimuat atau pohon default yang baru dibuat.
 */
int load_or_create_database(TreeNodePtr* head);

// Game logic functions

/*
 * Menjalankan logika tanya jawab dengan menelusuri pohon berdasarkan jawaban pengguna.
 * IS: Pointer menunjuk ke node pertanyaan saat ini.
 * FS: Pointer `last_accessed` menunjuk ke leaf node (jawaban/tebakan) yang dicapai.
 */
void choice(TreeNodePtr start, TreeNodePtr* last_accessed);

/*
 * Mengajukan pertanyaan konfirmasi akhir kepada pengguna apakah tebakan program benar.
 * IS: Program telah mencapai leaf node dan siap menebak.
 * FS: Mengembalikan 1 jika pengguna menjawab 'ya' (tebakan benar), 0 jika 'tidak'.
 */
int ask_if_animal(TreeNodePtr start);

/*
 * Membangun node pertanyaan baru berdasarkan input dari pengguna saat program salah menebak.
 * IS: Program salah menebak dan berada di leaf node yang tidak tepat.
 * FS: Leaf node tersebut diubah menjadi node pertanyaan baru dengan dua anak (jawaban benar dan salah).
 */
void build_question(TreeNodePtr start);

// Tree analysis functions

/*
 * Menampilkan semua hewan (leaf node) yang ada di dalam pohon.
 * IS: Pohon pengetahuan ada di memori.
 * FS: Daftar semua nama hewan tercetak di layar konsol.
 */
void display_all_animals(TreeNodePtr root);

/*
 * Menampilkan jalur pertanyaan dari root hingga ke hewan target.
 * IS: Pohon ada di memori dan nama hewan target diberikan.
 * FS: Jalur pertanyaan menuju hewan tersebut tercetak di layar.
 */
void show_learning_path(TreeNodePtr root, char* target_animal);

/*
 * Menghitung jumlah total hewan (leaf node) dalam pohon.
 * IS: Pohon pengetahuan ada di memori.
 * FS: Mengembalikan jumlah total hewan.
 */
int count_total_animals(TreeNodePtr root);

/*
 * Menghitung kedalaman (level maksimum) dari pohon.
 * IS: Pohon pengetahuan ada di memori.
 * FS: Mengembalikan nilai kedalaman pohon.
 */
int calculate_tree_depth(TreeNodePtr root);

/*
 * Menemukan dan menampilkan pertanyaan yang paling sering ditanyakan selama permainan.
 * IS: Pohon pengetahuan ada di memori.
 * FS: Daftar pertanyaan yang paling sering diajukan tercetak di layar.
 */
void find_most_asked_questions(TreeNodePtr root);

// Tree traversal with stack (iterative)

/*
 * Menelusuri dan menampilkan seluruh struktur pohon secara pre-order (Root-Left-Right).
 * IS: Pohon pengetahuan ada di memori.
 * FS: Struktur pohon tercetak di layar dengan format pre-order.
 */
void iterative_preorder_traversal(TreeNodePtr root);

/*
 * Menelusuri dan menampilkan seluruh struktur pohon secara in-order (Left-Root-Right).
 * IS: Pohon pengetahuan ada di memori.
 * FS: Struktur pohon tercetak di layar dengan format in-order.
 */
void iterative_inorder_traversal(TreeNodePtr root);

#endif