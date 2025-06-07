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

#endif // TREE_OPERATIONS_H
