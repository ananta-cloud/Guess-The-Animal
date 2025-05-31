#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "nazriel.h"

Node* createNode(char* data, int isAnimal) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    strcpy(newNode->data, data);
    newNode->isAnimal = isAnimal;
    newNode->right = NULL;
    newNode->left = NULL;
    return newNode;
}

void mainMenu() {
    printf("\n=== Guess The Animal ===\n");
    printf("1. Game\n");
    printf("2. Memory\n");
    printf("3. Edit Data\n");
    printf("4. Exit\n");
    printf("Choose an option: ");
}