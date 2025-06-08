#ifndef STACK_OPERATIONS_H
#define STACK_OPERATIONS_H

#include "common_types.h"

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
void save_current_state_before_learning(TreeNodePtr node);

#endif // STACK_OPERATIONS_H
