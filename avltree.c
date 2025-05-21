#include "avltree.h"
#include <stdio.h>
#include <stdlib.h>
AVLtree CreateTree(void){
    return NULL;
}
AVLtree MakeEmpty(AVLtree t){
    if(t != NULL){
        MakeEmpty(t->left);
        MakeEmpty(t->right);
        // Free the secondary list of nodes
        AVLtree current = t->next;
        while (current != NULL) {
            AVLtree temp = current;
            current = current->next;
            free(temp);
        }
        t->next = NULL;
        free(t);
    }
    return NULL;
}
void displayNode(AVLtree t){
    if (t == NULL){
        return;
    }
    printf("%s;%s;%d/%d/%d;%.2f;%d;%.2f\n", t->firstName,t->lastName,t->day,t->month,t->year,t->Height,t->weight,t->BMI);

    AVLtree current = t->next;
    while (current != NULL) {
        printf("%s;%s;%d/%d/%d;%.2f;%d;%.2f\n",
               current->firstName, current->lastName, current->day, current->month, current->year,
               current->Height, current->weight, current->BMI);

        current = current->next;
    }

}
AVLtree searchAVL(AVLtree t, float BMI){
    if(t->BMI == BMI){

    }
}
int AVLTreeHeight(AVLtree t)
{
    if (t == NULL)
        return -1;
    else
        return t->t_height;
}
AVLtree SingleRotateWithLeft(AVLtree k2){
    AVLtree k1;
    k1 = k2->right;
    k2->right = k1->left;
    k1->left = k2;

    //update height
    k1->t_height = Max(AVLTreeHeight(k1->left), AVLTreeHeight(k1->right))+1;
    k2->t_height = Max(AVLTreeHeight(k2->left), AVLTreeHeight(k2->right))+1;
    return k1;
}

AVLtree SingleRotateWithRight(AVLtree k2){
    AVLtree k1 = k2->left;
    k2->left = k1->right;
    k1->right = k2;

    //update height
    k1->t_height = Max(AVLTreeHeight(k1->left), AVLTreeHeight(k1->right))+1;
    k2->t_height = Max(AVLTreeHeight(k2->left), AVLTreeHeight(k2->right))+1;
    return k1;
}

AVLtree DoubleRotateWithLeft(AVLtree k3){
    k3->left = SingleRotateWithLeft(k3->left);
    return SingleRotateWithRight(k3);
}

AVLtree DoubleRotateWithRight(AVLtree k3){
    k3->right = SingleRotateWithRight(k3->right);
    return SingleRotateWithLeft(k3);
}

int Max(int x, int y){
    if (x >= y)
        return x;
    else
        return y;
}