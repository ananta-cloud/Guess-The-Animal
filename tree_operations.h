#ifndef TREE_OPERATIONS_H
#define TREE_OPERATIONS_H

#include "common_types.h"

// Fungsi untuk manajemen tree dasar
TreeNodePtr create_default_tree();
void free_tree(TreeNodePtr start);

// Fungsi untuk logika inti permainan
void choice(TreeNodePtr start, TreeNodePtr* last_accessed);
int ask_if_animal(TreeNodePtr start);
void build_question(TreeNodePtr start);

// Fungsi untuk File I/O dan manajemen database
void write_to_file(TreeNodePtr start, FILE* out_file);
int read_from_file(TreeNodePtr* start, FILE* in_file);
int auto_save_tree(TreeNodePtr start);
int load_or_create_database(TreeNodePtr* head);
#endif // TREE_OPERATIONS_H
