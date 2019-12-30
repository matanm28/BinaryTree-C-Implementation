#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define NODE_COUNT_DEFAULT 1
#define ROOT_DEFAULT_VALUE 0
#define IN_ORDER 1
#define PRE_ORDER 2
#define POST_ORDER 3
#define DELIM " "

typedef struct Node {
    int value;
    struct Node *left;
    struct Node *right;
} Node;

typedef struct Tree {
    int nodeCount;
    Node *root;
} Tree;

Node *createNode(int value) {
    Node *node = (Node *) malloc(sizeof(Node));
    node->value = value;
    node->left = NULL;
    node->right = NULL;
    return node;
}

Tree *createTree(int value) {
    Tree *tree = (Tree *) malloc(sizeof(Tree));
    tree->nodeCount = NODE_COUNT_DEFAULT;
    tree->root = createNode(value);
    return tree;
}

void deleteNode(Node* node){
    if (node == NULL){
        return;
    }
    deleteNode(node->left);
    free(node->left);
    deleteNode(node->right);
    free(node->right);
}

void deleteTree(Tree* tree){
    deleteNode(tree->root);
}

Tree *createTreeNoValue() {
    return createTree(ROOT_DEFAULT_VALUE);
}

Node *insertNode(Node *currNode, Node *newNode) {
    if (currNode == NULL) {
        return newNode;
    } else if (newNode->value >= currNode->value) {
        currNode->right = insertNode(currNode->right, newNode);
    } else {
        currNode->left = insertNode(currNode->left, newNode);
    }
}

void insert(Tree *tree, int value) {
    Node *newNode = createNode(value);
    tree->root = insertNode(tree->root, newNode);
}

void printNode(Node *node) {
    printf("%d", node->value);
}

void printInOrder(Node *node) {
    if (node == NULL) {
        return;
    }
    printInOrder(node->left);
    printNode(node);
    printf(DELIM);
    printInOrder(node->right);
}

void printPostOrder(Node *node) {
    if (node == NULL) {
        return;
    }
    printPostOrder(node->left);
    printPostOrder(node->right);
    printNode(node);
    printf(DELIM);
}

void printPreOrder(Node *node) {
    if (node == NULL) {
        return;
    }
    printNode(node);
    printf(DELIM);
    printPreOrder(node->left);
    printPreOrder(node->right);
}

void printTree(Tree *tree, int order) {
    switch (order) {
        case PRE_ORDER:
            printf("\nPre order traversal of binary tree is:\n");
            printPreOrder(tree->root);
            break;
        case POST_ORDER:
            printf("\nPost order traversal of binary tree is:\n");
            printPostOrder(tree->root);
            break;
        default:
        case IN_ORDER:
            printf("\nIn order traversal of binary tree is:\n");
            printInOrder(tree->root);
            break;
    }
}
Node* search(Node* node, int value){
    if (node == NULL || node->value == value){
        return node;
    } else if (value >= node->value){
        return search(node->right,value);
    } else {
        return search(node->left,value);
    }
}

Node* searchTree (Tree* tree, int value){
    return search(tree->root,value);
}


int main() {
    Tree *tree = createTree(5);
    insert(tree, 3);
    insert(tree, 2);
    insert(tree, 4);
    insert(tree, 9);
    insert(tree, 7);
    insert(tree, 10);
    printTree(tree, IN_ORDER);
    printTree(tree, POST_ORDER);
    printTree(tree, PRE_ORDER);
    int value = 7;
    Node* node = searchTree(tree,7);
    if (node !=NULL){
        printf("\nsearched and found: ");
        printNode(node);
        printf("\n");
    } else {
        printf("no node with value %d found \n", value);
    }
    value = 15;
    node = searchTree(tree,15);
    if (node !=NULL){
        printf("\nsearched and found: ");
        printNode(node);
        printf("\n");
    } else {
        printf("no node with value %d found \n", value);
    }
}