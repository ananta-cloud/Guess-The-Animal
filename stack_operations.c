#include "stack_operations.h"

/**
 * @brief Mendorong (push) state sebuah node ke undo stack.
 * @param node Node yang dimodifikasi.
 * @param original_text Teks asli dari node.
 * @param original_yes Pointer yes asli.
 * @param original_no Pointer no asli.
 * @param operation_type Jenis operasi (misal: "LEARN").
 */
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
}

/**
 * @brief Mengambil (pop) state dari undo stack.
 * @return 1 jika berhasil, 0 jika stack kosong.
 */
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
