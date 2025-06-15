#ifndef TREE_OPERATIONS_H
#define TREE_OPERATIONS_H

#include "../header.h"

// Tree management functions
TreeNodePtr create_default_tree();
void free_tree(TreeNodePtr start);
TreeNodePtr copy_node(TreeNodePtr original);

// File I/O operations
void write_to_file(TreeNodePtr start, FILE* out_file);
int read_from_file(TreeNodePtr* start, FILE* in_file);
int auto_save_tree(TreeNodePtr start);
int create_backup();
int load_or_create_database(TreeNodePtr* head);

// Game logic functions
void choice(TreeNodePtr start, TreeNodePtr* last_accessed);
int ask_if_animal(TreeNodePtr start);
void build_question(TreeNodePtr start);

// Tree analysis functions
void display_all_animals(TreeNodePtr root);
void show_learning_path(TreeNodePtr root, char* target_animal);
int count_total_animals(TreeNodePtr root);
int calculate_tree_depth(TreeNodePtr root);
void find_most_asked_questions(TreeNodePtr root);

// Tree traversal with stack (iterative)
void iterative_preorder_traversal(TreeNodePtr root);
void iterative_inorder_traversal(TreeNodePtr root);

#endif