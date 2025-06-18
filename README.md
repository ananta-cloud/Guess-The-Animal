# Guess-The-Animal
# Dokumentasi program tugas besar SDA Praktek D3 Teknik Informatika Semester 2 Politeknik Negeri Bandung Kelas 1B Kelompok 2
Anggota :  
|   Nama                         |     NIM   |
|:------------------------------ |:---------:|
| Dinanda Khayra Hutama         | 241511041 |
| Fahraj Ananta Aulia Arkan      | 241511042 |
| Nazriel Ramdhani         | 241511055 |


Animal Guessing Game
Animal Guessing Game adalah permainan tebak-tebakan berbasis teks yang menggunakan pohon biner keputusan untuk menebak hewan yang dipikirkan pengguna melalui pertanyaan ya/tidak. Program ini ditulis dalam bahasa C dengan desain modular, mendukung pembelajaran adaptif, mode single player dan multiplayer, statistik permainan, serta fitur administrasi. Proyek ini ideal untuk mempelajari struktur data seperti pohon biner, linked list, stack, dan queue, serta pengembangan aplikasi konsol.
Fitur Utama

Mode Permainan:
Single Player: Satu pemain melawan sistem.
Multiplayer: 2-8 pemain bergiliran dengan sistem antrian.

Pembelajaran Adaptif: Sistem belajar dari tebakan salah dengan menambahkan pertanyaan dan hewan baru ke pohon keputusan.
Manajemen Data:
Auto-save pohon keputusan ke file (animal_database.txt).
Backup dan restore database (animal_database_backup.txt).
Riwayat permainan disimpan di game_history.txt.

Statistik dan Analisis:
Riwayat permainan dengan timestamp.
Ranking pemain berdasarkan skor.
Saran pertanyaan terbaik berdasarkan tingkat keberhasilan.
Analisis pembelajaran sistem.

Fitur Admin:
Melihat struktur pohon keputusan.
Undo operasi pembelajaran.
Reset data, backup, dan restore sistem.

UI Ramah Pengguna:
Mendukung input multibahasa (Inggris dan Indonesia).
Tabel dan emoji untuk tampilan yang menarik.

Struktur Data:
Pohon biner untuk logika permainan.
Linked list untuk riwayat permainan.
Stack untuk undo.
Queue untuk antrian pemain di mode multiplayer.

Penggunaan

Jalankan program untuk melihat menu utama:

Pilih Single Player untuk bermain sendiri.
Pilih Multiplayer untuk bermain dengan 2-8 pemain.
Pilih Statistics untuk melihat riwayat, ranking, dan analisis.
Pilih Admin untuk fitur administrasi (lihat pohon, undo, reset, dll.).
Pilih Help untuk panduan.
Pilih Exit untuk keluar.

Cara Bermain:

Pikirkan seekor hewan.
Jawab pertanyaan ya/tidak dari sistem.
Jika sistem salah menebak, masukkan hewan dan pertanyaan baru untuk pembelajaran.
Skor: 10 poin untuk tebakan benar, 2 poin untuk partisipasi.


Mode Multiplayer:

Masukkan jumlah pemain (2-8) dan nama masing-masing.
Pemain bergiliran sesuai antrian, dengan statistik diperbarui setiap giliran.

Fitur Admin:

Lihat struktur pohon keputusan.
Batalkan operasi pembelajaran terakhir (undo).
Reset semua data (hati-hati, data akan hilang).
Buat atau pulihkan backup database.


Struktur Pohon Keputusan

Kedalaman: 5 level.
Pertanyaan:
Level 1: Apakah hewan memiliki tulang belakang?
Level 2: Habitat (air/darat).
Level 3: Karakteristik (insang, menyusui, cangkang, terbang, dll.).
Level 4: Detail (predator, ukuran, jumlah kaki, warna, dll.).
Level 5: Hewan (misalnya, Hiu, Kucing, Kupu-kupu).


Jumlah Hewan Awal: 16 (dapat bertambah melalui pembelajaran).

Contoh Output
======================================
       ANIMAL GUESSING GAME
======================================
1. Single Player
2. Multiplayer
3. Statistics
4. Admin
5. Help
6. Exit
Pilih opsi (1-6): 1

SETUP MODE SINGLE PLAYER
Masukkan nama Anda: Alice
Setup single player selesai!

GILIRAN: Alice
Pikirkan seekor hewan, dan saya akan mencoba menebaknya!

Apakah hewan ini memiliki tulang belakang? (ya/tidak): ya
Apakah hewan ini hidup di air? (ya/tidak): tidak
Apakah hewan ini menyusui? (ya/tidak): ya
Apakah hewan ini predator? (ya/tidak): ya
Apakah hewan ini Kucing? (ya/tidak): ya

Kontribusi
Proyek ini dikembangkan oleh tim yang terdiri dari Dinanda, Nazriel, dan Fahraj. Berikut adalah kontribusi masing-masing anggota serta fitur-fitur yang terdapat pada file yang mereka tangani:


Dinanda

File yang Ditangani: main.c, utils.c, utils.h, tree_operations.c, tree_operations.h
Kontribusi:
Merancang alur utama program di main.c, termasuk integrasi mode single player dan multiplayer, menu utama, dan manajemen sesi permainan.
Mengembangkan antarmuka pengguna (UI) di utils.c, termasuk menu, format tabel, dan pesan multibahasa dengan emoji.
Mengimplementasikan logika inti pohon biner di tree_operations.c, termasuk pembelajaran adaptif dan operasi file.
Menyediakan fitur administrasi seperti backup, restore, dan reset data.


Fitur pada File:
main.c:
Menu utama dengan opsi single player, multiplayer, statistik, admin, bantuan, dan keluar.
Logika permainan untuk single player dan multiplayer.
Manajemen sesi dan cleanup saat keluar.


utils.c, utils.h:
UI konsisten dengan header, separator, dan tabel.
Validasi input (get_valid_integer, get_valid_string).
Statistik permainan, analisis pembelajaran, dan status sistem.
Manajemen backup/restore dan reset data.
Aturan permainan dan panduan pengguna.


tree_operations.c, tree_operations.h:
Pohon keputusan dengan 16 hewan awal dan kedalaman 5 level.
Pembelajaran adaptif melalui build_question.
Operasi file untuk menyimpan/memuat pohon (write_to_file, read_from_file).
Analisis pohon (jumlah hewan, kedalaman, daftar hewan).
Traversal pohon secara iteratif (iterative_preorder_traversal).


Nazriel

File yang Ditangani: linked_list.c, linked_list.h, stack_operations.c, stack_operations.h
Kontribusi:
Mengimplementasikan manajemen riwayat permainan dan saran pertanyaan menggunakan linked list di linked_list.c.
Mengembangkan mekanisme undo menggunakan stack di stack_operations.c, memungkinkan pembatalan operasi pembelajaran.
Menyediakan fungsi untuk analisis statistik riwayat dan saran pertanyaan terbaik.
Mengimplementasikan stack untuk traversal pohon secara iteratif.


Fitur pada File:
linked_list.c, linked_list.h:
Riwayat permainan dengan nomor game, hewan, status tebakan, dan timestamp.
Auto-save riwayat ke file (game_history.txt).
Statistik permainan (total permainan, tebakan benar, tingkat keberhasilan).
Saran pertanyaan dengan success rate berbasis moving average.
Pencarian riwayat berdasarkan nomor game dan tampilan permainan terbaru.

stack_operations.c, stack_operations.h:
Stack untuk undo operasi pembelajaran (push_undo_state, undo_last_operation).
Riwayat undo dengan tampilan operasi sebelumnya.
Stack untuk traversal pohon secara iteratif (push_tree_node, pop_tree_node).
Manajemen memori stack yang efisien.


Fahraj

File yang Ditangani: queue_operations.c, queue_operations.h, common_types.c, common_types.h
Kontribusi:
Merancang sistem antrian pemain untuk mode multiplayer di queue_operations.c.
Mengembangkan struktur data dasar dan utilitas umum di common_types.c.
Menyediakan fungsi untuk manajemen pemain, termasuk ranking dan pembaruan statistik.
Memastikan input pengguna multibahasa dan robust melalui utilitas di common_types.c.


Fitur pada File:
queue_operations.c, queue_operations.h:
Antrian pemain untuk mode multiplayer (2-8 pemain).
Manajemen giliran pemain (rotate_to_next_player, start_player_turn).
Statistik pemain (skor, permainan dimainkan, tebakan benar, tingkat sukses).
Ranking pemain dengan bubble sort dan ikon medali (🥇, 🥈, 🥉).
Setup mode single player dan multiplayer.


common_types.c, common_types.h:
Definisi struktur data: TreeNode, GameHistory, UndoStack, Player, PlayerQueue, QuestionSuggestion.
Utilitas seperti trim_string, to_lowercase, dan get_answer untuk input multibahasa.
Formatting UI dengan print_separator dan print_header.
Konstanta untuk panjang teks dan nama file.

Terima kasih telah menggunakan Animal Guessing Game!  🐾
