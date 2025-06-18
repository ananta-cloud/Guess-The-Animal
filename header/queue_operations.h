#ifndef QUEUE_OPERATIONS_H
#define QUEUE_OPERATIONS_H

#include "common_types.h"

// Operasi Queue untuk manajemen pemain

/*
 * Membuat dan menginisialisasi antrian pemain baru yang kosong.
 * IS: Antrian belum ada di memori.
 * FS: Mengembalikan pointer ke antrian baru yang kosong.
 */
PlayerQueue* create_player_queue();

/*
 * Menambahkan pemain baru ke akhir antrian.
 * IS: Antrian berisi n pemain.
 * FS: Antrian berisi n+1 pemain, dengan pemain baru di posisi belakang (rear).
 */
void enqueue_player(PlayerQueue* queue, const char* name);

/*
 * Menghapus dan mengembalikan pemain dari depan antrian.
 * IS: Antrian berisi n pemain (n > 0).
 * FS: Antrian berisi n-1 pemain, dan pointer ke pemain yang dihapus dikembalikan.
 */
Player* dequeue_player(PlayerQueue* queue);

/*
 * Melihat pemain di depan antrian tanpa menghapusnya.
 * IS: Antrian berisi n pemain.
 * FS: Mengembalikan pointer ke pemain di posisi depan (front).
 */
Player* peek_current_player(PlayerQueue* queue);

/*
 * Memeriksa apakah antrian pemain kosong.
 * IS: Antrian ada di memori.
 * FS: Mengembalikan 1 jika kosong, 0 jika berisi pemain.
 */
int is_queue_empty(PlayerQueue* queue);

/*
 * Mengosongkan seluruh antrian pemain dan membebaskan memori.
 * IS: Antrian berisi n pemain.
 * FS: Antrian menjadi kosong dan semua memori pemain dibebaskan.
 */
void clear_player_queue(PlayerQueue* queue);

// Fungsi manajemen pemain

/*
 * Merotasi giliran dengan memindahkan pemain dari depan ke belakang antrian.
 * IS: Pemain A ada di depan antrian.
 * FS: Pemain A ada di belakang antrian, dan pemain B (sebelumnya di posisi kedua) kini di depan.
 */
void rotate_to_next_player();

/*
 * Menambahkan poin ke skor pemain.
 * IS: Pemain memiliki skor x.
 * FS: Pemain memiliki skor x + points.
 */
void update_player_score(Player* player, int points);

/*
 * Memperbarui statistik pemain (skor, jumlah main, tebakan benar) setelah satu ronde.
 * IS: Statistik pemain sebelum ronde dimainkan.
 * FS: Statistik pemain telah diperbarui sesuai hasil ronde.
 */
void update_player_stats(Player* player, int was_correct);

/*
 * Menampilkan informasi pemain yang sedang mendapat giliran.
 * IS: Giliran pemain saat ini.
 * FS: Informasi pemain (nama, skor, dll.) tercetak di layar.
 */
void display_current_player();

/*
 * Menampilkan daftar semua pemain beserta statistiknya dalam format tabel.
 * IS: Antrian berisi data semua pemain.
 * FS: Tabel berisi data semua pemain tercetak di layar.
 */
void display_all_players();

/*
 * Menampilkan peringkat pemain berdasarkan skor tertinggi.
 * IS: Antrian berisi data pemain dengan berbagai skor.
 * FS: Tabel peringkat pemain yang terurut tercetak di layar.
 */
void display_player_rankings();

// Fungsi untuk setup mode permainan

/*
 * Menjalankan proses setup untuk mode multiplayer (memasukkan jumlah dan nama pemain).
 * IS: Antrian pemain kosong atau berisi data dari sesi sebelumnya.
 * FS: Antrian pemain berisi pemain-pemain baru yang siap untuk bermain.
 */
int setup_multiplayer_mode();

/*
 * Menjalankan proses setup untuk mode single-player (memasukkan nama pemain).
 * IS: Antrian pemain kosong atau berisi data dari sesi sebelumnya.
 * FS: Antrian pemain berisi satu pemain yang siap bermain.
 */
int setup_single_player_mode();

// Fungsi untuk alur giliran pemain

/*
 * Menampilkan pesan awal untuk giliran seorang pemain.
 * IS: Giliran pemain akan dimulai.
 * FS: Pesan pembuka giliran tercetak di layar.
 */
void start_player_turn(Player* current_player);

/*
 * Memperbarui statistik dan menampilkan ringkasan setelah giliran seorang pemain selesai.
 * IS: Ronde permainan baru saja berakhir.
 * FS: Statistik pemain diperbarui dan ringkasan ronde tercetak di layar.
 */
void end_player_turn(Player* current_player, int was_correct);

// Fungsi statistik dan utilitas pemain

/*
 * Mencari dan mengembalikan pemain dengan skor tertinggi.
 * IS: Antrian berisi data pemain.
 * FS: Mengembalikan pointer ke pemain dengan skor tertinggi.
 */
Player* find_best_player();

/*
 * Mencari pemain berdasarkan nama.
 * IS: Antrian berisi data pemain.
 * FS: Mengembalikan pointer ke pemain dengan nama yang cocok, atau NULL jika tidak ditemukan.
 */
Player* find_player_by_name(const char* name);

/*
 * Menyimpan statistik semua pemain ke file.
 * IS: Statistik pemain ada di memori.
 * FS: File statistik pemain dibuat/diperbarui.
 */
void save_player_stats();

/*
 * Memuat statistik pemain dari file.
 * IS: Antrian pemain kosong.
 * FS: Antrian pemain diisi dengan data statistik dari file.
 */
void load_player_stats();

/*
 * Mendapatkan jumlah total pemain dalam antrian.
 * IS: Antrian berisi n pemain.
 * FS: Mengembalikan nilai n.
 */
int get_total_players();

#endif // QUEUE_OPERATIONS_H