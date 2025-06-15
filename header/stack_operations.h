#ifndef STACK_OPERATIONS_H
#define STACK_OPERATIONS_H

#include "../header.h"

// Operasi stack untuk fungsionalitas undo
void push_undo_state(TreeNodePtr node, const char* original_text, 
                     TreeNodePtr original_yes, TreeNodePtr original_no, 
                     const char* operation_type);

int pop_undo_state(TreeNodePtr* node, char* original_text, 
                   TreeNodePtr* original_yes, TreeNodePtr* original_no, 
                   char* operation_type);

int undo_last_operation(TreeNodePtr root);
void clear_undo_stack();
int is_undo_stack_empty();

int get_undo_stack_size();
void display_undo_history();
UndoStack* peek_undo_stack();
void save_current_state_before_learning(TreeNodePtr node);

// Struct untuk traversal tree
typedef struct TreeStack {
    TreeNodePtr node;
    struct TreeStack* next;
} TreeStack;

void push_tree_node(TreeStack** stack, TreeNodePtr node);
TreeNodePtr pop_tree_node(TreeStack** stack);
int is_tree_stack_empty(TreeStack* stack);
void clear_tree_stack(TreeStack** stack);

#endif // STACK_OPERATIONS_H
