#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include "common_types.h"

// Modul untuk Riwayat Permainan (Linked List)

/*
 * Menambahkan satu catatan riwayat permainan baru ke awal linked list.
 * IS: Daftar riwayat berisi n catatan.
 * FS: Daftar riwayat berisi n+1 catatan, dengan catatan baru di posisi terdepan.
 */
void add_game_history(int game_number, const char* animal, int was_correct);

/*
 * Menampilkan seluruh riwayat permainan yang tersimpan.
 * IS: Daftar riwayat berisi data permainan.
 * FS: Tabel riwayat permainan tercetak di layar.
 */
void display_game_history();

/*
 * Menghapus semua riwayat permainan dari memori.
 * IS: Daftar riwayat berisi n catatan.
 * FS: Daftar riwayat kosong, semua memori dibebaskan.
 */
void clear_game_history();

// Modul untuk manajemen file riwayat

/*
 * Menyimpan seluruh daftar riwayat dari memori ke file teks.
 * IS: Daftar riwayat berisi data di memori.
 * FS: File `game_history.txt` diperbarui dengan data riwayat saat ini.
 */
void save_history_to_file();

/*
 * Memuat data riwayat dari file teks ke dalam linked list di memori.
 * IS: Daftar riwayat di memori kosong.
 * FS: Daftar riwayat di memori berisi data yang telah dibaca dari file.
 */
void load_history_from_file();

// Modul untuk statistik permainan

/*
 * Menghitung jumlah total permainan yang pernah dimainkan.
 * IS: Daftar riwayat berisi n catatan.
 * FS: Mengembalikan nilai n.
 */
int get_total_games();

/*
 * Menghitung jumlah total tebakan benar.
 * IS: Daftar riwayat berisi data permainan.
 * FS: Mengembalikan jumlah permainan dengan status 'benar'.
 */
int get_correct_guesses();

/*
 * Menghitung persentase tingkat keberhasilan tebakan.
 * IS: Daftar riwayat berisi data permainan.
 * FS: Mengembalikan nilai persentase (0-100).
 */
double get_success_rate();

/*
 * Menampilkan ringkasan statistik permainan (total main, benar, salah, rate).
 * IS: Daftar riwayat berisi data permainan.
 * FS: Tampilan ringkasan statistik tercetak di layar.
 */
void display_game_statistics();

// Modul untuk saran pertanyaan

/*
 * Menambahkan atau memperbarui data sebuah pertanyaan dalam daftar saran.
 * IS: Daftar saran berisi n pertanyaan.
 * FS: Data untuk pertanyaan yang diberikan diperbarui, atau pertanyaan baru ditambahkan.
 */
void add_question_suggestion(const char* question, int was_successful);

/*
 * Mendapatkan saran pertanyaan terbaik berdasarkan tingkat keberhasilan dan penggunaan.
 * IS: Daftar saran berisi data pertanyaan.
 * FS: Mengembalikan string berisi pertanyaan terbaik.
 */
char* get_best_question_suggestion();

/*
 * Menampilkan daftar saran pertanyaan.
 * IS: Daftar saran berisi data pertanyaan.
 * FS: Tabel berisi saran pertanyaan tercetak di layar.
 */
void display_question_suggestions();

/*
 * Memperbarui tingkat keberhasilan sebuah pertanyaan.
 * IS: Pertanyaan memiliki tingkat sukses x.
 * FS: Tingkat sukses pertanyaan diperbarui berdasarkan hasil permainan terakhir.
 */
void update_question_success_rate(const char* question, int was_successful);

/*
 * Menghapus semua data saran pertanyaan dari memori.
 * IS: Daftar saran berisi n pertanyaan.
 * FS: Daftar saran menjadi kosong.
 */
void clear_suggestions();

// Modul untuk riwayat

/*
 * Mencari data riwayat permainan berdasarkan nomor gamenya.
 * IS: Daftar riwayat berisi data permainan.
 * FS: Mengembalikan pointer ke catatan riwayat yang cocok, atau NULL jika tidak ditemukan.
 */
GameHistory* find_game_by_number(int game_number);

/*
 * Menampilkan beberapa permainan terakhir sesuai jumlah yang diminta.
 * IS: Daftar riwayat berisi data permainan.
 * FS: Daftar permainan terakhir tercetak di layar.
 */
void display_recent_games(int count);

#endif // LINKED_LIST_H
