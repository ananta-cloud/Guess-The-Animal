#ifndef UTILS_H
#define UTILS_H

#include "common_types.h"
#include <conio.h>

// Menu and UI functions

/*
 * Mencetak tampilan menu utama.
 * IS: Layar konsol.
 * FS: Tampilan menu utama tercetak di layar dengan opsi yang disorot.
 */
void print_main_menu(int highlighted_option);

/*
 * Mencetak tampilan menu permainan.
 * IS: Layar konsol.
 * FS: Tampilan menu permainan tercetak di layar dengan opsi yang disorot.
 */
void print_game_menu(int highlighted_option);

/*
 * Mencetak tampilan menu statistik.
 * IS: Layar konsol.
 * FS: Tampilan menu statistik tercetak di layar dengan opsi yang disorot.
 */
void print_statistics_menu(int highlighted_option);

/*
 * Mencetak tampilan menu admin.
 * IS: Layar konsol.
 * FS: Tampilan menu admin tercetak di layar dengan opsi yang disorot.
 */
void print_admin_menu(int highlighted_option);

/*
 * Mengelola navigasi menu interaktif menggunakan keyboard.
 * IS: Pengguna berada dalam sebuah menu.
 * FS: Mengembalikan nomor pilihan pengguna setelah tombol Enter ditekan.
 */
int get_menu_selection(int max_choice, void (*print_menu_func)(int));

/*
 * Mencetak teks di tengah layar konsol.
 * IS: Layar konsol.
 * FS: Teks tercetak di tengah layar.
 */
void print_centered(const char* text);

/*
 * Mencetak prompt di tengah layar konsol tanpa baris baru.
 * IS: Layar konsol.
 * FS: Prompt tercetak di tengah layar, siap untuk input pengguna.
 */
void prompt_centered(const char* text);

/*
 * Mencetak prompt yang rata kiri, sejajar dengan batas header.
 * IS: Layar konsol.
 * FS: Prompt tercetak rata kiri sesuai margin yang ditentukan.
 */
void print_aligned_prompt(const char* prompt);

/*
 * Membersihkan layar konsol.
 * IS: Layar konsol berisi teks.
 * FS: Layar konsol menjadi kosong.
 */
void clear_screen();

/*
 * Mendapatkan lebar terminal/konsol saat ini dalam satuan karakter.
 * IS: Jendela konsol memiliki lebar tertentu.
 * FS: Mengembalikan nilai lebar jendela.
 */
int get_terminal_width();

// Game flow functions

/*
 * Menampilkan layar selamat datang.
 * IS: Program baru saja dimulai.
 * FS: Pesan selamat datang tercetak di layar.
 */
void print_welcome();

/*
 * Menampilkan layar perpisahan.
 * IS: Program akan segera berakhir.
 * FS: Pesan perpisahan tercetak di layar.
 */
void print_goodbye();

/*
 * Menjeda program dan menunggu pengguna menekan Enter untuk melanjutkan.
 * IS: Sebuah proses telah selesai ditampilkan.
 * FS: Program melanjutkan eksekusi setelah Enter ditekan, dan layar dibersihkan.
 */
void ready();

/*
 * Menanyakan kepada pengguna apakah ingin bermain lagi.
 * IS: Satu ronde permainan telah selesai.
 * FS: Mengembalikan 1 jika pengguna ingin main lagi, 0 jika tidak.
 */
int play_again();

/*
 * Menampilkan aturan permainan.
 * IS: Pengguna memilih opsi bantuan.
 * FS: Daftar aturan permainan tercetak di layar.
 */
void display_game_rules();

// System functions

/*
 * Menginisialisasi semua sistem yang diperlukan di awal program.
 * IS: Variabel global dan data belum dimuat.
 * FS: Riwayat permainan telah dimuat dan variabel global siap digunakan.
 */
void initialize_system();

/*
 * Membersihkan semua alokasi memori dan menyimpan data sebelum program ditutup.
 * IS: Program akan berakhir, data ada di memori.
 * FS: Data tersimpan ke file dan memori dibebaskan.
 */
void cleanup_system();

/*
 * Menghapus semua data permainan (database, riwayat, dll.) dan mengembalikannya ke keadaan default.
 * IS: File-file data berisi catatan permainan.
 * FS: File-file data dihapus dan program kembali ke keadaan awal seperti baru diinstal.
 */
void reset_all_data();

/*
 * Membuat salinan cadangan dari file-file data penting.
 * IS: File data utama ada.
 * FS: File cadangan (backup) dibuat atau diperbarui.
 */
int create_system_backup();

/*
 * Mengembalikan data dari file cadangan.
 * IS: File data utama mungkin rusak atau ingin dikembalikan ke versi sebelumnya.
 * FS: File data utama ditimpa dengan data dari file cadangan.
 */
int restore_system_backup();

// Input validation functions

/*
 * Meminta dan memvalidasi input integer dari pengguna dalam rentang tertentu.
 * IS: Program memerlukan input angka dari pengguna.
 * FS: Mengembalikan nilai integer yang valid.
 */
int get_valid_integer(int min, int max);

/*
 * Meminta dan memvalidasi input string dari pengguna.
 * IS: Program memerlukan input teks dari pengguna.
 * FS: Buffer diisi dengan string yang valid dari pengguna.
 */
void get_valid_string(char* buffer, int max_length, const char* prompt);

/*
 * Menampilkan pesan konfirmasi dan meminta jawaban ya/tidak dari pengguna.
 * IS: Sebuah tindakan kritis akan dilakukan.
 * FS: Mengembalikan 1 jika pengguna setuju, 0 jika tidak.
 */
int confirm_action(const char* action);

// Display functions

/*
 * Menampilkan ringkasan statistik yang komprehensif.
 * IS: Data permainan dan pemain ada di memori.
 * FS: Tampilan statistik lengkap tercetak di layar.
 */
void display_comprehensive_statistics();

/*
 * Menampilkan analisis performa pembelajaran sistem.
 * IS: Data riwayat permainan ada di memori.
 * FS: Tampilan analisis pembelajaran tercetak di layar.
 */
void display_learning_analytics();

/*
 * Menampilkan status sistem saat ini (file, memori, performa).
 * IS: Program sedang berjalan.
 * FS: Tampilan status sistem tercetak di layar.
 */
void display_system_status();

/*
 * Menampilkan layar bantuan yang berisi informasi cara bermain dan fitur.
 * IS: Pengguna memilih opsi bantuan.
 * FS: Tampilan informasi bantuan tercetak di layar.
 */
void show_help_information();

// Time utility functions

/*
 * Mengubah data waktu (timestamp) menjadi format string yang mudah dibaca.
 * IS: Data waktu dalam format `time_t`.
 * FS: Mengembalikan string berisi tanggal dan waktu (misal: "18/06/2025 12:40:00").
 */
char* format_timestamp(time_t timestamp);

/*
 * Menghitung berapa hari telah berlalu sejak permainan terakhir.
 * IS: Riwayat permainan ada di memori.
 * FS: Mengembalikan jumlah hari.
 */
int get_days_since_last_play();

/*
 * Menampilkan ringkasan sesi permainan saat pengguna akan keluar dari program.
 * IS: Program akan ditutup.
 * FS: Tampilan ringkasan sesi (total main, rate, dll.) tercetak di layar.
 */
void display_session_summary();

#endif