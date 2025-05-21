#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "avltree.h"

AVLtree loadPatients(char*);
AVLtree insertPatients(AVLtree, struct Node *);
void displayPatients(AVLtree);
AVLtree infoPatients(AVLtree, float);
void youngestPatient(AVLtree);
void Menu();
int main(int argc, char *argv[]){
    if(argc > 1){
        FILE *infile = fopen(argv[1], "r");
        if (infile == NULL) {
            perror("\nError with argument!");
            exit(1);
        } else{
            printf("\nValid argument");
            fclose(infile);
        }
    }

    AVLtree patients = loadPatients(argv[1]);
    if(patients == NULL){
        printf("\nFailed Tree memory Allocation!");
        exit(1);
    }
    int option;
    do {
        Menu();
        scanf("%d", &option);
        if(option == 1){
            displayPatients(patients);
                    }
        else if(option == 2){
            AVLtree result = patients;
            do {
                float BMI;
                printf("\nEnter your patient's BMI :");
                scanf("%f", &BMI);
                result = infoPatients(patients, BMI);
            } while (result == NULL);
    }
        else if(option == 3){
            youngestPatient(patients);
        }
        else if(option!= 4){
            printf("\nInvalid option");
        }
        fflush(stdin);
    } while (option != 4);

    MakeEmpty(patients);
    return 0;
}
AVLtree loadPatients(char* fileName){
    FILE *file = fopen(fileName, "r");
    if(file == NULL){
        printf("\nFailed file opening");
        exit(1);
    }
    AVLtree tree = CreateTree();
    Node *new;
    while((new = (Node *) malloc(sizeof(Node))) != NULL && fscanf(file,"%19[^;];%19[^;];%d/%d/%d;%f;%d;%f", new->firstName, new->lastName, &new->day,&new->month,&new->year,&new->Height, &new->weight, &new->BMI )== 8) {
        tree = insertPatients(tree, new);
        new->next = NULL;
    }
    return tree;
}
AVLtree insertPatients(AVLtree t , struct Node *newNode){
    if (t == NULL){
        t = newNode;
        t->t_height = 0;
        t->left = t->right = NULL;
    }
    else if(newNode->BMI < t->BMI){
        t->left = insertPatients(t->left,newNode);
        if (AVLTreeHeight(t->left) - AVLTreeHeight(t->right) == 2){
            if(newNode->BMI < t->BMI)
                t = SingleRotateWithRight(t);
            else
                t = DoubleRotateWithLeft(t);
        }
    }
    else if(newNode->BMI > t->BMI){
        t->right = insertPatients(t->right,newNode);
        if(AVLTreeHeight(t->left) - AVLTreeHeight(t->right) == 2)
            if(newNode->BMI > t->BMI)
                t = SingleRotateWithLeft(t);
            else
                t = DoubleRotateWithRight(t);
    }
    else if(newNode->BMI == t->BMI){
        if(t->next == NULL){
            t->next = newNode;
        }
        else{
            AVLtree current = t;
            while (current->next != NULL){
                current = current->next;
            }
            current->next = newNode;
        }
        newNode->next = NULL;
    }
    t->t_height = Max(AVLTreeHeight(t->left), AVLTreeHeight(t->right)) + 1;

    return t;

}
void displayPatients(AVLtree t){
    if(t!= NULL){
        displayPatients(t->left);
        printf("\n%s;%s;%d/%d/%d;%.2f;%d;%.2f", t->firstName,t->lastName,t->day,t->month,t->year,t->Height,t->weight,t->BMI);

        // Traverse and print duplicate nodes
        AVLtree current = t->next;
        while (current != NULL) {
            printf("%s;%s;%d/%d/%d;%.2f;%d;%.2f\n",
                   current->firstName, current->lastName, current->day, current->month, current->year,
                   current->Height, current->weight, current->BMI);

            current = current->next;
        }

        displayPatients(t->right);
    }

}
void findYoungestPatient(AVLtree t, struct Node** young) {
    if (t == NULL) {
        return;
    }

    // Check the current node against the youngest so far
    if (*young == NULL ||
        t->year > (*young)->year ||
        (t->year == (*young)->year && t->month > (*young)->month) ||
        (t->year == (*young)->year && t->month == (*young)->month && t->day > (*young)->day)) {
        *young = t;
    }

    // Traverse duplicates in the linked list
    AVLtree current = t->next;
    while (current != NULL) {
        if (current->year > (*young)->year ||
            (current->year == (*young)->year && current->month > (*young)->month) ||
            (current->year == (*young)->year && current->month == (*young)->month && current->day > (*young)->day)) {
            *young = current;
        }
        current = current->next;
    }

    // Recurse on left and right children
    findYoungestPatient(t->left, young);
    findYoungestPatient(t->right, young);
}

void youngestPatient(AVLtree t) {
    struct Node* youngest = NULL;

    if (t == NULL) {
        printf("\nNo patients in the tree.\n");
        return;
    }

    // Find the youngest patient
    findYoungestPatient(t, &youngest);

    // Print the youngest patient
    if (youngest != NULL) {
        printf("\nThe youngest patient is %s %s",
               youngest->firstName, youngest->lastName);
    } else {
        printf("\nNo patients in the tree.\n");
    }
}


//the complexity of the function is O(n), since we have to compare every single node in the tree
//Function can be improved by having a pointer to the youngest patient. With every insertion the new node would only be compared to the current youngest.
//With this implementation, the complexity would be O(1) as we would just display the node that is being pointed at.

AVLtree infoPatients(AVLtree t, float BMI) {
    while (t != NULL) {
        if (BMI == t->BMI) {
            displayNode(t);
            return t;
        } else if (BMI < t->BMI) {
            t = t->left;
        } else {
            t = t->right;
        }
    }
    printf("\nThere is not an available patient who has a BMI of %.1f\n", BMI);
    return NULL;
}
//the time complexity is O(logn + k) where log n is the height of the tree and k is the number of duplicates since it O(k) time to traverse the linked list of duplicates on each node if there exists any!


void Menu(){
    printf("\n-------MENU------");
    printf("\n(1)Display the full index of patients"
           "\n(2)Display the details of the patients"
           "\n(3)Display the youngest patient"
           "\n(4)Exit");
    printf("\nEnter your option:");

}