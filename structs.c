#include <stdio.h>
#include <stdlib.h>
//Defines both a normal and a double linked list, Binary Search Tree, and a Graph
//Includes Add Node, Prrint, Search for a Value, and Delete Nodes

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


typedef struct Graph{
    Vertex** vertices;
    int size;
} Graph;


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
    printf("\nRoot Value: %d", root->value);
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

void bstdelete(BstNode** root, int target){
    if((*root) == NULL){return;}
    if ((*root)->value == target) {
    BstNode* tmp = *root;

    if ((*root)->left == NULL && (*root)->right == NULL) {
        *root = NULL;
        free(tmp);
        return;
    }

    if ((*root)->left == NULL) {
        *root = (*root)->right;
        free(tmp);
        return;
    }

     if ((*root)->right == NULL) {
        *root = (*root)->left;
        free(tmp);
        return;
    }


    BstNode* succ = (*root)->right;
    while (succ->left != NULL) succ = succ->left;

    (*root)->value = succ->value;                 // copy value up
    bstdelete(&(*root)->right, succ->value);      // delete successor node in right subtree
    return;
    }
    
    if((*root)->value > target){
        bstdelete(&(*root)->left, target);
    }else{
        bstdelete(&(*root)->right, target);
    }

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
    bstdelete(&root, 6);
    bstdelete(&root, 5);
    bstdelete(&root, 9);
    bstprint(root);
    
    printf("\nEnd of BST Test"); 
}



Vertex* createVertex(int value, Graph** g){
    Vertex* v = malloc(sizeof(Vertex));
    
    if(v == NULL){
        return NULL;
    }

    v->value = value;
    v->edges = NULL;


    (*g)->vertices[(*g)->size] = v;
    (*g)->size++;


    return v;
}

void createEdge(Vertex** v, Vertex** u){
    Edge* e = malloc(sizeof(Edge));
    e->to = *(u);
    e->next = NULL;

    if((*v)->edges == NULL){
        (*v)->edges = e;
    }else{
        while((*v)->edges->next != NULL){
            (*v)->edges = (*v)->edges->next;
        }
        (*v)->edges->next = e;
    }
    return;
}

Graph* createGraph(int size){ //Made 60% GPT 40% 
    Graph* g = malloc(sizeof(Graph));
    if(g==NULL){return NULL;}
    g->vertices = malloc(size*sizeof(Vertex*));
    g->size = 0;
    return g;
}


void deleteVertex(Vertex** v, Graph** g){
    // 1) Remove all incoming edges to *v (do NOT destroy adjacency list heads)
    for(int i = 0; i < (*g)->size; i++){
        Vertex* u = (*g)->vertices[i];
        if(u == NULL) continue;

        Edge** cur = &u->edges;              // cursor to the link we're currently at
        while(*cur != NULL){
            if((*cur)->to == (*v)){
                Edge* temp = *cur;
                *cur = temp->next;           // unlink
                free(temp);
                temp = NULL;
            }else{
                cur = &(*cur)->next;         // advance
            }
        }
    }

    // 2) Remove the vertex from the vertices array (shift only from its index)
    int idx = -1;
    for(int j = 0; j < (*g)->size; j++){
        if((*g)->vertices[j] == (*v)){
            idx = j;
            break;
        }
    }

    if(idx != -1){
        for(int j = idx; j < (*g)->size - 1; j++){
            (*g)->vertices[j] = (*g)->vertices[j+1];
        }
        (*g)->vertices[(*g)->size - 1] = NULL;
        (*g)->size--;
    }

    // 3) Free outgoing edges from *v (avoid leaks)
    Edge* e = (*v)->edges;
    while(e != NULL){
        Edge* temp = e;
        e = e->next;
        free(temp);
    }
    (*v)->edges = NULL;

    // 4) Free the vertex itself
    free(*v);
    *v = NULL;
    return;
}


void graphtest(){
    Graph* graph= createGraph(5);
    Vertex* A = createVertex(5, &graph);
    Vertex* B = createVertex(10, &graph);
    Vertex* C = createVertex(15, &graph);

    printf("\nValue for A:    %d",A->value);
    printf("\nValue for B:    %d",B->value);
    printf("\nValue for C:    %d",C->value);
    printf("\nSize of Graph:  %d",graph->size);
    
    createEdge(&A, &B);
    createEdge(&B, &C);
    createEdge(&A, &C);
    printf("\nTransverse A(%d) to C(%d)", A->value ,A->edges->to->edges->to->value);
    deleteVertex(&B, &graph);
    printf("\n%d",A->edges->to->value);


    return;
}







int main(){
    slltest();
    dlltest();
    bsttest();
    graphtest();
    return 0;
}
