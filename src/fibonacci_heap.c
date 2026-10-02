#include<stdio.h>
#include<stdlib.h>
#include<limits.h>

struct Node{
    int key;
    int degree;
    struct Node* parent;
    struct Node* child;
    struct Node* left;
    struct Node* right;
    int mark;
};


struct FibonacciHeap{
    struct Node* min;
    int n;
};


struct Node* createNode(int key);
struct FibonacciHeap* createFibonacciHeap();
void insert(struct FibonacciHeap* H, int key);
void link(struct Node* y, struct Node* x);
void consolidate(struct FibonacciHeap* H);
struct Node* extractMin(struct FibonacciHeap* H);
void decreaseKey(struct FibonacciHeap* H, struct Node* x, int k);
void cut(struct FibonacciHeap* H, struct Node* x, struct Node* y);
void cascadingCut(struct FibonacciHeap* H, struct Node* y);
void deleteNode(struct FibonacciHeap* H, struct Node* x);
struct Node* findNode(struct Node* H, int k);
void display(struct FibonacciHeap* H);
void displayNode(struct Node* n);



struct Node* createNode(int key){
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->key = key;
    node->degree = 0;
    node->parent = NULL;
    node->child = NULL;
    node->left = node;
    node->right = node;
    node->mark = 0;
    return node;
}


struct FibonacciHeap* createFibonacciHeap(){
    struct FibonacciHeap* H = (struct FibonacciHeap*)malloc(sizeof(struct FibonacciHeap));
    H->min = NULL;
    H->n = 0;
    return H;
}


void insert(struct FibonacciHeap* H, int key){
    struct Node* node = createNode(key);
    if (H->min == NULL){
        H->min = node;
    }
    else{
        node->left = H->min;
        node->right = H->min->right;
        H->min->right->left = node;
        H->min->right = node;
        if (key < H->min->key){
            H->min = node;
        }
    }
    H->n++;
}



struct Node* extractMin(struct FibonacciHeap* H){
    struct Node* z = H->min;
    if (z != NULL) {
        if (z->child != NULL){
            struct Node* x = z->child;
            do {
                struct Node* next = x->right;
                x->left->right = x->right;
                x->right->left = x->left;
                x->left = H->min;
                x->right = H->min->right;
                H->min->right->left = x;
                H->min->right = x;
                x->parent = NULL;
                x = next;
            }
            while (x != z->child);
        }
        z->left->right = z->right;
        z->right->left = z->left;
        if (z == z->right){
            H->min = NULL;
        } else{
            H->min = z->right;
            consolidate(H);
        }
        H->n--;
    }
    return z;
}



void link(struct Node* y, struct Node* x){
    y->left->right = y->right;
    y->right->left = y->left;
    y->parent = x;
    if (x->child == NULL){
        x->child = y;
        y->right = y;
        y->left = y;
    }
    else{
        y->left = x->child;
        y->right = x->child->right;
        x->child->right->left = y;
        x->child->right = y;
    }
    x->degree++;
    y->mark = 0;
}


void consolidate(struct FibonacciHeap* H){
    int D = 45;
    struct Node* A[D];
    for (int i = 0; i < D; i++){
        A[i] = NULL;
    }
    struct Node* w = H->min;
    do {
        struct Node* x = w;
        int d = x->degree;
        while (A[d] != NULL){
            struct Node* y = A[d];
            if (x->key > y->key){
                struct Node* temp = x;
                x = y;
                y = temp;
            }
            link(y, x);
            A[d] = NULL;
            d++;
        }
        A[d] = x;
        w = w->right;
    } while (w != H->min);
    H->min = NULL;
    for (int i = 0; i < D; i++){
        if (A[i] != NULL) {
            if (H->min == NULL){
                H->min = A[i];
                H->min->left = H->min;
                H->min->right = H->min;
            } else {
                A[i]->left = H->min;
                A[i]->right = H->min->right;
                H->min->right->left = A[i];
                H->min->right = A[i];
                if (A[i]->key < H->min->key){
                    H->min = A[i];
                }
            }
        }
    }
}



void decreaseKey(struct FibonacciHeap* H, struct Node* x, int k){
    if (k > x->key){
        printf("New key is greater than current key\n");
        return;
    }
    x->key = k;
    struct Node* y = x->parent;
    if (y != NULL && x->key < y->key){
        cut(H, x, y);
        cascadingCut(H, y);
    }
    if (x->key < H->min->key){
        H->min = x;
    }
}



void cut(struct FibonacciHeap* H, struct Node* x, struct Node* y){
    if (x->right == x){
        y->child = NULL;
    } else {
        x->right->left = x->left;
        x->left->right = x->right;
        if (y->child == x){
            y->child = x->right;
        }
    }
    y->degree--;
    x->left = H->min;
    x->right = H->min->right;
    H->min->right->left = x;
    H->min->right = x;
    x->parent = NULL;
    x->mark = 0;
}



void cascadingCut(struct FibonacciHeap* H, struct Node* y){
    struct Node* z = y->parent;
    if (z != NULL) {
        if (y->mark == 0){
            y->mark = 1;
        } else {
            cut(H, y, z);
            cascadingCut(H, z);
        }
    }
}



void deleteNode(struct FibonacciHeap* H, struct Node* x){
    decreaseKey(H, x, INT_MIN);
    extractMin(H);
}




void menu(){

    printf("\nFibonacci Heap Operations:\n");
    printf("1. Insert\n");
    printf("2. Extract Min\n");
    printf("3. Decrease Key\n");
    printf("4. Delete Node\n");
    printf("5. Display Heap\n");
    printf("6. Exit\n");
}



int main(){
    struct FibonacciHeap* H = createFibonacciHeap();
    int choice, key, newKey;
    struct Node* node;

    while (1){
        menu();
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter key to insert: ");
                scanf("%d", &key);
                insert(H, key);
                break;
            case 2:
                node = extractMin(H);
                if (node != NULL){
                    printf("Extracted min: %d\n", node->key);
                    free(node);
                }
                else{
                    printf("Heap is empty\n");
                }
                break;
            case 3:
                printf("Enter current key: ");
                scanf("%d", &key);
                printf("Enter new key: ");
                scanf("%d", &newKey);
                node = findNode(H->min, key);
                if (node != NULL){
                    decreaseKey(H, node, newKey);
                }
                else{
                    printf("Node not found\n");
                }
                break;
            case 4:
                printf("Enter key to delete: ");
                scanf("%d", &key);
                node = findNode(H->min, key);
                if (node != NULL){
                    deleteNode(H, node);
                }

                else{

      printf("Node not found\n");
                }
                break;
            case 5:
                display(H);
                break;
            case 6:
                exit(0);
            default:
                printf("Invalid choice\n");
        }
    }
    return 0;
}



struct Node* findNode(struct Node* H, int k){
    struct Node* x = H;
    if (x == NULL){
        return NULL;
    }
    do {
        if (x->key == k){
            return x;
        }
        struct Node* found = findNode(x->child, k);
        if (found != NULL){
            return found;
        }
        x = x->right;
    }
    while (x != H);
    return NULL;
}



void display(struct FibonacciHeap* H){
    if (H->min == NULL){
        printf("Heap is empty\n");
        return;
    }
    printf("Root nodes in the Fibonacci Heap:\n");
    struct Node* x = H->min;
    do {
        displayNode(x);
        x = x->right;
    }
    while (x != H->min);
    printf("\n");
}


void displayNode(struct Node* n){
    printf("%d ", n->key);
    struct Node* x = n->child;
    if (x != NULL){
        do {
            displayNode(x);
            x = x->right;
        } while (x != n->child);
    }
}



