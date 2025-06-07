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
                   
#endif // STACK_OPERATIONS_H
