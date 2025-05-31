#ifndef NAZRIEL_H
#define NAZRIEL_H

typedef struct Node {
    char data[100];      
    int isAnimal;        
    struct Node* right;  
    struct Node* left;   
} Node;

void mainMenu();

#endif