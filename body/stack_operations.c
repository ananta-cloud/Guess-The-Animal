#include "../header/stack_operations.h"

void push_undo_state(TreeNodePtr node, const char* original_text, 
                     TreeNodePtr original_yes, TreeNodePtr original_no, 
                     const char* operation_type) {
    UndoStack* new_undo = (UndoStack*)malloc(sizeof(UndoStack));
    if (new_undo == NULL) {
        printf("Error: Tidak cukup memory untuk undo stack!\n");
        return;
    }
    
    new_undo->modified_node = node;
    strncpy(new_undo->original_text, original_text, MAX_TEXT_LENGTH - 1);
    new_undo->original_text[MAX_TEXT_LENGTH - 1] = '\0';
    new_undo->original_yes = original_yes;
    new_undo->original_no = original_no;
    strncpy(new_undo->operation_type, operation_type, 19);
    new_undo->operation_type[19] = '\0';
    new_undo->next = undo_stack_top;
    
    undo_stack_top = new_undo;
    
    printf("State disimpan untuk undo (Operasi: %s)\n", operation_type);
}

int pop_undo_state(TreeNodePtr* node, char* original_text, 
                   TreeNodePtr* original_yes, TreeNodePtr* original_no, 
                   char* operation_type) {
    if (undo_stack_top == NULL) {
        return 0; // Stack kosong
    }
    
    UndoStack* top = undo_stack_top;
    
    *node = top->modified_node;
    strcpy(original_text, top->original_text);
    *original_yes = top->original_yes;
    *original_no = top->original_no;
    strcpy(operation_type, top->operation_type);
    
    undo_stack_top = top->next;
    free(top);
    
    return 1; // Sukses
}

int undo_last_operation(TreeNodePtr root) {
    if (is_undo_stack_empty()) {
        printf("Tidak ada operasi yang dapat dibatalkan!\n");
        return 0;
    }
    
    TreeNodePtr node;
    char original_text[MAX_TEXT_LENGTH];
    TreeNodePtr original_yes, original_no;
    char operation_type[20];
    
    if (pop_undo_state(&node, original_text, &original_yes, &original_no, operation_type)) {
        // mengembalikan keadaan Node
        strcpy(node->text, original_text);
        
        // Membebaskan node yang baru dibuat jika operasi yang dilakukan adalah "LEARN"
        if (strcmp(operation_type, "LEARN") == 0) {
            if (node->yes_ans && node->yes_ans != original_yes) {
                free(node->yes_ans);
            }
            if (node->no_ans && node->no_ans != original_no) {
                free(node->no_ans);
            }
        }
        
        node->yes_ans = original_yes;
        node->no_ans = original_no;
        
        printf("Operasi '%s' berhasil dibatalkan!\n", operation_type);
        printf("Node dikembalikan ke: \"%s\"\n", original_text);
        return 1;
    }
    
    return 0;
}

void clear_undo_stack() {
    while (undo_stack_top != NULL) {
        UndoStack* temp = undo_stack_top;
        undo_stack_top = undo_stack_top->next;
        free(temp);
    }
    printf("Undo stack telah dibersihkan.\n");
}

int is_undo_stack_empty() {
    return undo_stack_top == NULL;
}

void save_current_state_before_learning(TreeNodePtr node) {
    if (node == NULL) return;
    push_undo_state(node, node->text, node->yes_ans, node->no_ans, "LEARN");
}

int get_undo_stack_size() {
    int count = 0;
    UndoStack* current = undo_stack_top;
    while (current != NULL) {
        count++;
        current = current->next;
    }
    return count;
}

void display_undo_history() {
    if (is_undo_stack_empty()) {
        printf("Tidak ada riwayat undo.\n");
        return;
    }
    
    print_header("RIWAYAT OPERASI UNDO");
    printf("%-5s %-15s %-40s\n", "No", "Jenis Operasi", "Text Asli");
    printf("----------------------------------------------------------------\n");
    
    UndoStack* current = undo_stack_top;
    int count = 1;
    
    while (current != NULL) {
        printf("%-5d %-15s %-40s\n", 
               count,
               current->operation_type,
               current->original_text);
        current = current->next;
        count++;
    }
    printf("\nTotal operasi yang dapat di-undo: %d\n\n", count - 1);
}

UndoStack* peek_undo_stack() {
    return undo_stack_top;
}

void push_tree_node(TreeStack** stack, TreeNodePtr node) {
    TreeStack* new_stack_node = (TreeStack*)malloc(sizeof(TreeStack));
    if (new_stack_node == NULL) {
        printf("Error: Tidak cukup memory untuk tree stack!\n");
        return;
    }
    
    new_stack_node->node = node;
    new_stack_node->next = *stack;
    *stack = new_stack_node;
}

TreeNodePtr pop_tree_node(TreeStack** stack) {
    if (*stack == NULL) return NULL;
    
    TreeStack* top = *stack;
    TreeNodePtr node = top->node;
    *stack = top->next;
    free(top);
    
    return node;
}

int is_tree_stack_empty(TreeStack* stack) {
    return stack == NULL;
}

void clear_tree_stack(TreeStack** stack) {
    while (*stack != NULL) {
        pop_tree_node(stack);
    }
}