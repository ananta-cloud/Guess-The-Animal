#ifndef TREE_OPERATIONS_H
#define TREE_OPERATIONS_H

#include "common_types.h"

// Fungsi untuk manajemen tree dasar
TreeNodePtr create_default_tree();
void free_tree(TreeNodePtr start);

// Fungsi untuk File I/O dan manajemen database
void write_to_file(TreeNodePtr start, FILE* out_file);
int read_from_file(TreeNodePtr* start, FILE* in_file);
int auto_save_tree(TreeNodePtr start);
int load_or_create_database(TreeNodePtr* head);
int create_backup();

// Fungsi untuk logika inti permainan
void choice(TreeNodePtr start, TreeNodePtr* last_accessed);
int ask_if_animal(TreeNodePtr start);
void build_question(TreeNodePtr start);

// --- FUNGSI ANALISIS TREE BARU ---
int count_total_animals(TreeNodePtr root);
int calculate_tree_depth(TreeNodePtr root);
void display_all_animals(TreeNodePtr root);
void iterative_preorder_traversal(TreeNodePtr root); 
#endif // TREE_OPERATIONS_H
