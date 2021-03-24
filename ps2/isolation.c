#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


typedef struct tree {
    int key;
    struct tree *left;
    struct tree *right;
    struct tree *parent;
} node;

node *create(node *root, int key);
node *add(node *root, int key);

bool compare_two_trees(node* tree1, node* tree2) {
    if (tree1 == NULL && tree2 == NULL) {
        return true;
    }
    if (tree1 == NULL || tree2 == NULL) {
        return false;
    }
    return compare_two_trees(tree1->left, tree2->left) && compare_two_trees(tree1->right, tree2->right);
}

int main(void) {
    int a, b;
    scanf("%i %i", &a, &b);

    //int mainArr[a][b];
    int **mainArr = (int **)calloc(a, sizeof(int *));
    if (mainArr == NULL) {
        free(mainArr);
        mainArr = NULL;
        exit(1);
    }
    for(int i = 0; i < a; i++) {
        mainArr[i] = (int *)calloc(b, sizeof(int));
        if (mainArr == NULL) {
            free(mainArr);
            mainArr = NULL;
            exit(1);
        }
    }

    // заполняем главную матрицу входными данными
    for (int i = 0; i < a; ++i) {
        for (int j = 0; j < b; ++j) {
            scanf("%i", &mainArr[i][j]);
        }
    }
    node* trees[a];
    
    node* tree = NULL;

    for (int i = 0; i < a; ++i) {
        tree = create(tree, mainArr[i][0]);
        trees[i] = tree;
        
        for (int j = 1; j < b; j++) {
            tree = add(tree, mainArr[i][j]);
        }
        //preorderf(tree);
        //printf("\n");

    }
    int result = a;
    
    for (int i = 0; i < a; ++i) {
        for (int j = i + 1; j < a; ++j) {
            if (compare_two_trees(trees[i], trees[j]) == true) {
                result--;
                break;
            }
        }
    }
    //result = a - result + 1;
    printf("%d\n", result);
    
    
    
    for(int i = 0; i < a; i++) free(mainArr[i]);
    free(mainArr);
    free(tree);
    return 0;
}




node *create(node *root, int key)
{
    node *tmp = malloc(sizeof(node));
    tmp -> key = key;
    tmp -> parent = NULL;
    tmp -> left = tmp -> right = NULL;
    root = tmp;
    return root;
}

node *add(node *root, int key)
{
    node *root2 = root, *root3 = NULL;
    node *tmp = malloc(sizeof(node));
    tmp -> key = key;
    while (root2 != NULL)
    {
        root3 = root2;
        if (key < root2 -> key)
            root2 = root2 -> left;
        else
            root2 = root2 -> right;
    }

    tmp -> parent = root3;
    tmp -> left = NULL;
    tmp -> right = NULL;
    if (key < root3 -> key) root3 -> left = tmp;
    else root3 -> right = tmp;
    return root;
}


