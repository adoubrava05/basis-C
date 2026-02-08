#include <stdio.h>
#include <stdlib.h>


//Single Linked List
typedef struct SllNode{
    int value;
    struct SllNode* next;
}SllNode;  

//Double Linked List
typedef struct DllNode{
    int value;
    struct DllNode* next;
    struct DllNode* prev;
}DllNode;

//Binary Tree
typedef struct BstNode{
    int value;
    struct BstNode* left;
    struct BstNode* right;
} BstNode;

//Graph
typedef struct Edge Edge;
typedef struct Vertex{
    int value;
    struct Edge* edges;
} Vertex;

typedef struct Edge{
    struct Vertex* to;
    struct Edge* next;
} Edge;

void sllcreateNode(SllNode** root,int value){
    SllNode* a = malloc(sizeof(SllNode));
    if(a == NULL){return;}
    a->next = NULL;
    a->value = value;

    if((*root) == NULL){\
        //printf("\nChanging Root:    %d",a->value);
        (*root) = a;
    }else{
        //printf("\nAdding: %d", a->value);
        SllNode* curr = (*root);
        while(curr->next != NULL){
            curr = curr->next;
           //printf("\n%d", curr->value);
        }
        curr->next = a;
    }
    return;
}
void sllprint(SllNode* root){
    SllNode* curr = root;
    int i = 0;
    while(curr->next != NULL){
        printf("\nNode %d is %d and its next is %d",i,curr->value,curr->next->value);
        curr = curr->next;
        i++;
    }
   printf("\nNode %d is %d and its next is NULL",i,curr->value); 
    return;
}
void slldelete(SllNode** root, int target){
    printf("\nDeleting %d", target); 
    SllNode* curr = (*root);
    SllNode* prev = NULL;
    if((*root) == NULL){return;}

    if((*root)->value == target){
        SllNode* tmp = (*root);
        (*root) = (*root)->next;
        free(tmp);
        return;
    }else{
        while(curr && curr->value != target) {
            prev = curr;
            curr = curr->next;
        }
        if(curr == NULL){printf("\n%d not found",target);return;}
        prev->next = curr->next;
    }

    free(curr);
    return;
}
void slltest(){
    printf("\nStarting SLL Tests:");
    SllNode* root = NULL;
    sllcreateNode(&root, 1);
    sllcreateNode(&root, 2);
    sllcreateNode(&root, 3);
    sllcreateNode(&root, 4);
    sllcreateNode(&root, 7);
    printf("\nRoot Value: %d", root->value);
    sllprint(root);
    slldelete(&root,3);
    slldelete(&root, 1);
    slldelete(&root, 5);
    sllprint(root);
    printf("\nEnd of SLL Tests\n");
    return;
}
void dllcreateNode(DllNode** root, int value){
    DllNode* n = malloc(sizeof(DllNode));
    if(n==NULL){return;}
    n->value = value;
    n->next = NULL;
    n->prev = NULL;
    if((*root) == NULL){
        (*root) = n;
    }else{
        DllNode* curr = (*root);
        while(curr->next != NULL){
            curr = curr->next;
        }
        curr->next = n;
        curr->next->prev = curr;
    }
    return;
}
void dllprint(DllNode* root){
    DllNode* curr = root;
    int i = 0;
    if(curr == NULL){printf("\nEmtpy List");return;}
    printf("\nNode %d is %d, its prev is NULL and its next is %d",i,curr->value,curr->next->value);
    i++;
    curr = curr->next;
    while(curr->next != NULL){
        printf("\nNode %d is %d, its prev is %d and its next is %d",i,curr->value,curr->prev->value, curr->next->value); 
       i++;
       curr = curr->next;
    }
    printf("\nNode %d is %d, its prev is %d and its next is NULL",i,curr->value,curr->prev->value);
    return;
}
void dlldelete(DllNode** root, int target){
    printf("\nDeleting %d", target);
    if((*root) == NULL){printf("\nEmpty List");return;}
    DllNode* curr = (*root);
    if((*root)->value == target){
        DllNode* tmp = (*root);
        (*root) = (*root)->next;
        free(tmp);
        return;
    }else{
        while(curr && curr->value != target){
            curr = curr->next;
        }
        if(!curr){printf("\n%d not present", target);return;}
        
        DllNode* prev = curr->prev;
        DllNode* next = curr->next;
        prev->next = next;
        next->prev = prev;
    }
    free(curr);
    return;
}
void dlltest(){
    printf("\nStarting DLL Tests:");
    DllNode* root = NULL;
    dllcreateNode(&root, 1);
    dllcreateNode(&root, 2);
    dllcreateNode(&root, 3);
    dllcreateNode(&root, 4);
    dllcreateNode(&root, 7);
    printf("\nRoot Value: %d", root->next->next->next->next->prev->prev->prev->prev->value);
    dllprint(root);
    dlldelete(&root,3);
    dlldelete(&root, 1);
    dlldelete(&root, 5);
    dllprint(root);
    printf("\nEnd of DLL Tests\n");
    return; 
}


void bstnodecreate(BstNode** root, int value){
    BstNode* n = malloc(sizeof(BstNode));
    if(n == NULL){return;}
    
    n->value = value;
    n->left = NULL;\
    n->right = NULL;

    if(!(*root)){(*root) = n; return;}

    BstNode* curr = (*root);
    BstNode* prev = NULL;
    
    while(curr != NULL){
        prev = curr;
        if(n->value >= curr->value){
            curr = curr->right;
        }else{
            curr = curr->left;
        }
    }
    if(prev->value > n->value){
        prev->left = n;
    }else{
        prev->right = n;
    }
}

void bstprint(BstNode* root){
    if(root->left){
        bstprint(root->left);
    }
    printf("\nValue of Node is: %d",root->value);
    if(root->right){
        bstprint(root->right);
    }
    return;
}
 


void bstsearch(BstNode* root, int target){
    if(root == NULL){printf("\nNot Found: %d",target);}
    else if(root->value == target){printf("\nFound:   %d", target);return;}

    if(root->value > target && root->left){
        bstsearch(root->left, target);
        //printf("\nMoving left for %d",target);
    }else if (root->value < target && root->right){
        bstsearch(root->right, target);
        //printf("\nMoving right for %d",target);
    }else{
        printf("\nNot Found:    %d", target);
    }
    return;
}




void bsttest(){
    printf("\nStarting BST Test");
    BstNode* root = NULL;
    bstnodecreate(&root, 5);
    bstnodecreate(&root, 7);
    bstnodecreate(&root, 3);
    bstnodecreate(&root, 6);
    bstnodecreate(&root, 2);
    bstnodecreate(&root, 4);
    bstnodecreate(&root, 1);
    bstnodecreate(&root, 8);
    bstprint(root);
    bstsearch(root, 4);
    bstsearch(root, 8);
    bstsearch(root, 9);
    
    printf("\nEnd of BST Test"); 
}




int main(){
    slltest();
    dlltest();
    bsttest();
    return 0;
}
