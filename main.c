#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define NODE_COUNT_DEFAULT 0
#define ROOT_DEFAULT_VALUE 0
#define DELIM ","
#define RELATION_OPERATOR >


enum Traversal {
    IN_ORDER = 1, PRE_ORDER, POST_ORDER
};

typedef struct Node {
    int value;
    struct Node *left;
    struct Node *right;
} Node;


typedef struct Tree {
    int nodeCount;
    Node *root;
} Tree;

Node *search(Node *node, int value);

Node *searchTree(Tree *tree, int value);
Node *createNode(int value) {
    Node *node = (Node *) malloc(sizeof(Node));
    node->value = value;
    node->left = NULL;
    node->right = NULL;
    return node;
}

Tree *createTree() {
    Tree *tree = (Tree *) malloc(sizeof(Tree));
    tree->nodeCount = NODE_COUNT_DEFAULT;
    tree->root = NULL;
    return tree;
}

void deleteNode(Node *node) {
    if (node == NULL) {
        return;
    }
    deleteNode(node->left);
    //free(node->left);
    deleteNode(node->right);
    //free(node->right);
    free(node);
}

void deleteTree(Tree *tree) {
    deleteNode(tree->root);
}

Node *insertNode(Node *currNode, Node *newNode) {
    if (currNode == NULL) {
        return newNode;
    } else if (newNode->value RELATION_OPERATOR currNode->value) {
        currNode->right = insertNode(currNode->right, newNode);
    } else {
        currNode->left = insertNode(currNode->left, newNode);
    }
}

void insert(Tree *tree, int value) {
    if (searchTree(tree, value) != NULL) {
        return;
    }
    if (tree->nodeCount == 0) {
        tree->root = createNode(value);
    } else {
        Node *newNode = createNode(value);
        tree->root = insertNode(tree->root, newNode);
    }
    tree->nodeCount++;
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

void printTree(Tree *tree, enum Traversal order) {
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
    printf("\b\n");
}

Node *search(Node *node, int value) {
    if (node == NULL || node->value == value) {
        return node;
    } else if (value RELATION_OPERATOR node->value) {
        return search(node->right, value);
    } else {
        return search(node->left, value);
    }
}

Node *searchTree(Tree *tree, int value) {
    return search(tree->root, value);
}

void searchAndPrint(Tree *tree, int value) {
    Node *node = searchTree(tree, value);
    printf("\n");
    if (node != NULL) {
        printf("searched and found: ");
        printNode(node);
    } else {
        printf("no node with value %d found", value);
    }
    printf("\n");
}


int main() {
    Tree *tree = createTree();
    insert(tree, 5);
    insert(tree, 3);
    insert(tree, 2);
    insert(tree, 4);
    insert(tree, 9);
    insert(tree, 7);
    insert(tree, 10);
    printTree(tree, IN_ORDER);
    printTree(tree, POST_ORDER);
    printTree(tree, PRE_ORDER);
    searchAndPrint(tree, 7);
    searchAndPrint(tree, 15);
    deleteTree(tree);
}