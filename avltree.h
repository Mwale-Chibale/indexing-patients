typedef struct Node *AVLtree;
typedef struct Node{
    char firstName[20];
    char lastName[20];
    int day;
    int month;
    int year;
    float Height;
    int weight;
    float BMI;

    AVLtree left;
    AVLtree right;
    AVLtree next; // for same BMI instance
    int t_height;
}Node;


#ifndef CNG213A3_AVLTREE_H
#define CNG213A3_AVLTREE_H
AVLtree CreateTree(void);
AVLtree MakeEmpty(AVLtree);
int Max(int , int );
void displayNode(AVLtree);
int AVLTreeHeight(AVLtree);
AVLtree SingleRotateWithLeft(AVLtree k2);
AVLtree SingleRotateWithRight(AVLtree k2);
AVLtree DoubleRotateWithLeft(AVLtree k3);
AVLtree DoubleRotateWithRight(AVLtree k3);
#endif //CNG213A3_AVLTREE_H
