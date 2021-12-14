/// Бинарное Дерево int-ов

#include <stdlib.h>
#include <stdio.h>

typedef struct Vertex {
    int value;
    struct Vertex* left;
    struct Vertex* right;
} Vertex;

Vertex * push(Vertex* root, int value) {
    if (root) {
        // Переходим дальше
        if (value < root->value) {
            root->left = push(root->left, value);
        } else {
            root->right = push(root->right, value);
        }
    } else {
        // Добавляем новую вершину
        root = calloc(1, sizeof(Vertex));
        root->value = value;
        /// Зануление не нужно - calloc уже
    }
    return root;
}


Vertex * clean(Vertex* root) {
    if (root) {
        root->left = clean(root->left);
        root->right = clean(root->right);
        free(root);
    }
    return NULL;
}

void print(Vertex * root) {
    if (!root) {
        return;
    }
    print(root->left);
    printf("%d\n", root->value);
    print(root->right);
}

int main() {
//    int x = 0;
//    printf("%d\n", ++x);
//    printf("%d\n", x++);
//    printf("%d\n", x++);
//    printf("%d\n", ++x);
//
//    while (it++) {
//
//    }

    int value;
    Vertex * root2 = NULL;
    while (scanf("%d", &value) == 1) {
        root2 = push(root2, value);
    }
    print(root2);
    clean(root2);

    Vertex * root = NULL;
    root = push(root, 1);
    root = push(root, -1);
    root = push(root, 3);
    root = push(root, 7);
    print(root);
    clean(root);
}
