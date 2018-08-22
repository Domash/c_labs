#include <mm_malloc.h>
#include <stdbool.h>
#include <stdio.h>

int getInt() {
    int res;
    while(true) {
        if(scanf("%d", &res) && getchar() == '\n') {
            return res;
        } else {
            printf("Try again\n");
            while(getchar() != '\n') {}
        }
    }
}

typedef int T;

//int pos = 0;
int f = 0;

#define CMP_EQ(a, b) ((a) == (b))
#define CMP_LT(a, b) ((a) < (b))
#define CMP_GT(a, b) ((a) > (b))

int sizeOfTree = 0;

typedef struct TreeNode {
    T data;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;


TreeNode* getFreeNode(T value) {
    TreeNode* tmp = (TreeNode*) malloc(sizeof(TreeNode));
    tmp->left = tmp->right = NULL;
    tmp->data = value;
    return tmp;
}

void insert(TreeNode **head, int value) {
    TreeNode *tmp = NULL;
    if (*head == NULL) {
        *head = getFreeNode(value);
        f++;
        return;
    }
    
    tmp = *head;
    while (tmp) {
        if (CMP_GT(value, tmp->data)) {
            if (tmp->right) {
                tmp = tmp->right;
                continue;
            } else {
                tmp->right = getFreeNode(value);
                return;
            }
        } else if (CMP_LT(value, tmp->data)) {
            if (tmp->left) {
                tmp = tmp->left;
                continue;
            } else {
                tmp->left = getFreeNode(value);
                return;
            }
        } else {
            exit(2);
        }
    }
}

TreeNode * minValueNode(TreeNode* node) {
    TreeNode* current = node;
    while (current->left != NULL)
        current = current->left;
    
    return current;
}

TreeNode *addToBST(int arr[], int start, int end) {
    if(end < start) return NULL;
    int mid = (start + end) / 2;
    
    TreeNode *r = getFreeNode(arr[mid]);
    r->left = addToBST(arr, start, mid - 1);
    r->right = addToBST(arr, mid + 1, end);
    return r;
}

TreeNode *createMinimalBST(int arr[], int size) {
    return addToBST(arr, 0, size - 1);
}

void TreeToArray(TreeNode *node, int a[], int *pos) {
    if(node != NULL){
        if(node -> left )
            TreeToArray(node->left, a, pos);
        a[(*pos)++] = node->data;
        if(node -> right)
            TreeToArray(node->right, a, pos);
    }
}

void clearTree(TreeNode *node) {
    if(node != NULL) {
        clearTree(node->left);
        clearTree(node->right);
        free(node);
    }
}

void printTree(TreeNode *node, int step) {
    if (node == NULL) return;
    printTree(node->right, step + 2);
    for(int i = 0; i < step; ++i) {
        printf(" ");
    }
    printf("%d\n", node->data);
    printTree(node->left, step + 2);
}

TreeNode *search(TreeNode* root, int value){
    return !root ? NULL : root->data == value ? root :
    search(value > root->data ? root->right : root->left, value);
}

void menu(TreeNode *root) {
    int val, sizeOfTree = 0;
    bool ok = true;
    while(ok) {
        printf("1.Add element to Tree\n");
        printf("2.Balance Tree\n");
        printf("3.Print Tree\n");
        printf("4.EXIT\n");
        
        int command = getInt();
        switch (command) {
            case 1:
                val = getInt();
                if(search(root, val) == NULL) {
                    insert(&root, val);
                    sizeOfTree++;
                }
                break;
            case 2: {
                int *a = (int*)malloc(sizeof(int) * sizeOfTree);
                for(int i = 0; i < sizeOfTree; ++i) {
                    a[i] = 0;
                }
                int pos = 0;
                TreeToArray(root, a, &pos);
                clearTree(root);
                root = NULL;
                root = createMinimalBST(a, sizeOfTree);
               
                free(a);
            }
                break;
            case 3:
                printTree(root, 0);
                printf("\n");
                break;
            case 4:
                return;
                break;
            default:
                printf("Invalid operation, try again\n");
                break;
        }
    }
}

int main()
{
    TreeNode *root = (TreeNode*) malloc(sizeof(TreeNode));
    root = NULL;
    menu(root);
    
    printf("\nf = %d\n\n", f);
    
    clearTree(root);
    free(root);
    
    return 0;
}












