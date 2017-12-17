/* Chuong Viet Truong
 * Chvtruon
 * CMPS 101
 * PA 5
 */

#include <stdio.h>
#include <stdlib.h>
#include "List.h"
#include "Graph.h"

#define WHITE 0
#define GRAY 1
#define BLACK 2

void visit(Graph G, List S, int u, int *time);

typedef struct GraphObj{
    List *neighbors;
    int *color;
    int *parent;
    int *discover;
    int *finish;

    int order;
    int size;
}GraphObj;

// Constructors-Deconstructors
Graph newGraph(int n){
    Graph graph = malloc(sizeof(struct GraphObj));
    graph->neighbors = calloc(n+1, sizeof(List));
    graph->color = calloc(n+1, sizeof(int));
    graph->parent = calloc(n+1, sizeof(int));
    graph->discover = calloc(n+1, sizeof(int));
    graph->finish = calloc(n+1, sizeof(int));

    graph->order = n;
    graph->size = 0;
    for(int i = 1; i <= n; i++){
        graph->neighbors[i] = newList();
        graph->color[i] = WHITE;
        graph->parent[i] = NIL;
        graph->discover[i] = UNDEF;
        graph->finish[i] = UNDEF;
    }
    return graph;
}

void freeGraph(Graph* pG){
    Graph T = *pG;
    for(int i = 1; i<= getOrder(T); i++){
        freeList(&(T->neighbors[i]));
    }
    free(T->neighbors);
    free(T->color);
    free(T->parent);
    free(T->discover);
    free(T->finish);
    free(*pG);
    *pG = NULL;
}

// Access functions
int getOrder(Graph G){
    if(G == NULL){
        printf("Graph Error: calling getOrder() on NULL Graph reference\n");
        exit(1);
    }
    return G->order;
}

int getSize(Graph G){
    if(G == NULL){
        printf("Graph Error: calling getSize() on NULL Graph reference\n");
        exit(1);
    }
    return G->size;
}

int getParent(Graph G, int u){
    if(G == NULL){
        printf("Graph Error: calling getParent() on NULL Graph reference\n");
        exit(1);
    }
    return G->parent[u];
}

int getDiscover(Graph G, int u){
    if(G == NULL){
        printf("Graph Error: calling getDiscover() on NULL Graph reference\n");
        exit(1);
    }
    return G->discover[u];
}

int getFinish(Graph G, int u){
    if(G == NULL){
        printf("Graph Error: calling getFinish() on NULL Graph reference\n");
        exit(1);
    }
    return G->finish[u];
}

// Manipulation Procedures

void addEdgeHelper(List list, int x){
    if(length(list) == 0){
        append(list, x);
        return;
    }
    for(moveFront(list); index(list) != -1; moveNext(list)){
        if(x < get(list)){
            insertBefore(list, x);
            break;
        }
    }
    if(index(list) == -1){
        append(list, x);
    }
}

void addEdge(Graph G, int u, int v){
    if(G == NULL){
        printf("Graph Error: calling addEdge() on NULL Graph reference\n");
        exit(1);
    }
    if(u < 1 || u > getOrder(G)){
        printf("Graph Error: calling addEdge() on out of bounds u\n");
        exit(1);
    }
    if(v < 1 || v > getOrder(G)){
        printf("Graph Error: calling addEdge() on out of bounds v\n");
        exit(1);
    }
    addEdgeHelper(G->neighbors[u], v);
    addEdgeHelper(G->neighbors[v], u);
    G->size++;
}

void addArc(Graph G, int u, int v){
    if(G == NULL){
        printf("Graph Error: calling addArc() on NULL Graph reference\n");
        exit(1);
    }
    if(u < 1 || u > getOrder(G)){
        printf("Graph Error: calling addArc() on out of bounds u\n");
        exit(1);
    }
    if(v < 1 || v > getOrder(G)){
        printf("Graph Error: calling addArc() on out of bounds v\n");
        exit(1);
    }
    addEdgeHelper(G->neighbors[u], v);
    G->size++;
}

void DFS(Graph G, List S){
    if(G == NULL){
        printf("Graph Error: calling DFS() on NULL Graph reference\n");
        exit(1);
    }
    if (S == NULL) {
		printf("List Error: DFS() called on NULL List pointer\n");
		exit(1);
    }
    if(length(S) != getOrder(G)){
        printf("Graph Error: calling DFS() on invalid List\n");
        exit(1);
    }
    // DFS algorithm
    for(int i = 1; i <= getOrder(G); i++){
        G->color[i] = WHITE;
        G->parent[i] = NIL;
        G->discover[i] = UNDEF;
        G->finish[i] = UNDEF;
    }
    int time = 0;
    for(moveFront(S); index(S) != -1; moveNext(S)){
        int u = get(S);
        if(G->color[u] == WHITE){
            visit(G, S, u, &time);
        }
    }
    for (int i = 0; i < getOrder(G); i++){
        deleteBack(S);
    }
}

void visit(Graph G, List S, int u, int *time){
    if(G == NULL){
        printf("Graph Error: calling visit() on NULL Graph reference\n");
        exit(1);
    }
    if (S == NULL || time == NULL) {
        printf("Error: calling visit() with null pointers\n");
        exit (1);
    }
    G->color[u] = GRAY;
    G->discover[u] = ++(*time);
    List L = G->neighbors[u];
    for(moveFront(L); index(L) != -1; moveNext(L)){
        int y = get(G->neighbors[u]);
        if(G->color[y] == WHITE){
            G->parent[y] = u;
            visit(G, S, y, time);
        }
    }
    G->color[u] = BLACK;
    G->finish[u] = ++(*time);
    prepend(S, u);
}

// Other Functions
Graph transpose(Graph G){
    if(G == NULL){
        printf("Graph Error: calling transpose() on NULL Graph reference\n");
        exit(1);
    }

    Graph T = newGraph(getOrder(G));
    for(int i = 1; i <= getOrder(G); i++){
        List L = G->neighbors[i];
        for(moveFront(L); index(L) != -1; moveNext(L)){
            addArc(T, get(G->neighbors[i]), i);
        }
    }
    return T;

}

Graph copyGraph(Graph G){
    if(G == NULL){
        printf("Graph Error: calling copyGraph() on NULL Graph reference\n");
        exit(1);
    }

    Graph copy = newGraph(getOrder(G));
    for(int i = 1; i <= getOrder(G); i++) {
        moveFront(G->neighbors[i]);
        while(index(G->neighbors[i]) != -1) {
            addArc(copy, i, get(G->neighbors[i]));
            moveNext(G->neighbors[i]);
        }
    }
    return copy;
}

void printGraph(FILE* out , Graph G){
    if(G == NULL){
        printf("Graph Error: calling printGraph() on NULL Graph reference\n");
        exit(1);
    }
    for(int i = 1; i <= getOrder(G); i++){
        fprintf(out, "%d:", i);
        printList(out, G->neighbors[i]);
        fprintf(out, "\n");
    }
}
