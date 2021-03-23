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

int compare_two_trees(node* tree1, node* tree2) {
    if (tree1 == NULL && tree2 == NULL) {
        return 1;
    }
    if (tree1 == NULL || tree2 == NULL) {
        return 0;
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
    int result = 0;
    
    for (int i = 0; i < a; ++i) {
        for (int j = 0; j < a; ++j) {
            if (i != j && compare_two_trees(trees[i], trees[j])) ++result;
        }
    }
    result = a - result + 1;
    printf("%d\n", result);
    
    
    
    for(int i = 0; i < a; i++) free(mainArr[i]);
    free(mainArr);
    free(tree);
    return 0;
}




node *create(node *root, int key)
{
// Выделение памяти под корень дерева
    node *tmp = malloc(sizeof(node));
// Присваивание значения ключу
    tmp -> key = key;
// Присваивание указателю на родителя значения NULL
    tmp -> parent = NULL;
// Присваивание указателю на левое и правое поддерево значения NULL
    tmp -> left = tmp -> right = NULL;
    root = tmp;
    return root;
}

node *add(node *root, int key)
{
    node *root2 = root, *root3 = NULL;
// Выделение памяти под узел дерева
    node *tmp = malloc(sizeof(node));
// Присваивание значения ключу
    tmp -> key = key;
/* Поиск нужной позиции для вставки (руководствуемся правилом
вставки элементов, см. начало статьи, пункт 3) */
    while (root2 != NULL)
    {
        root3 = root2;
        if (key < root2 -> key)
            root2 = root2 -> left;
        else
            root2 = root2 -> right;
    }
/* Присваивание указателю на родителя значения указателя root3
(указатель root3 был найден выше) */
    tmp -> parent = root3;
// Присваивание указателю на левое и правое поддерево значения NULL
    tmp -> left = NULL;
    tmp -> right = NULL;
/* Вставляем узел в дерево (руководствуемся правилом
вставки элементов, см. начало статьи, пункт 3) */
    if (key < root3 -> key) root3 -> left = tmp;
    else root3 -> right = tmp;
    return root;
}


