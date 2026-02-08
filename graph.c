#include <stdlib.h>
#include <stdio.h>
//Delete Vertex
//Delete Edge
//Free Graph
//Print Graph
typedef struct Vertex Vertex ;
typedef struct Edge Edge;
typedef struct Graph Graph;

typedef struct Edge{
    Vertex* to; //Connected Vertex
    Edge* next; //Linked List of Edges
}Edge;

typedef struct Vertex{
    int value; //Value held in each vertices
    Edge* edges; //Linked List of all edges between this Vertex and other vertices
}Vertex;

typedef struct Graph{
    Vertex** vertices;
    int size;

}Graph;

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


int main(){
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


    return 0;
}

