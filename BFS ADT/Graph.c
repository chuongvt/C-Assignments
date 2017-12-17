/* Chuong Viet Truong
 * Chvtruon
 * CMPS 101
 * PA 4
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Graph.h"

#define WHITE 0
#define GRAY 1
#define BLACK 2

typedef struct GraphObj{
    List *neighbors;
    int *color;
    int *parent;
    int *distance;
    int order;
    int size;
    int source;
}GraphObj;

typedef struct GraphObj* Graph;

/*** Constructors-Destructors ***/

/* Returns a Graph pointing to a newly created GraphObj representing a graph
having n vertices and no edges */
Graph newGraph(int n){
    Graph graph = malloc(sizeof(struct GraphObj));
    graph->neighbors = calloc(n+1, sizeof(List));
    graph->color = calloc(n+1, sizeof(int));
    graph->parent = calloc(n+1, sizeof(int));
    graph->distance = calloc(n+1, sizeof(int));
    graph->order = n;
    graph->size = 0;
    graph->source = NIL;

    for(int i = 1; i <= n; i++){
        graph->neighbors[i] = newList();
        graph->color[i] = WHITE;
        graph->parent[i] = NIL;
        graph->distance[i] = INF;
    }
    return graph;
}

/* Frees all dynamic memory associated with the Graph *pG,then sets the handle
*pG to NULL */
void freeGraph(Graph* pG){
    Graph T = *pG;
    for(int i = 1; i <= getOrder(T); i++){
        freeList(&(T->neighbors[i]));
    }
    free(T->neighbors);
    free(T->color);
    free(T->parent);
    free(T->distance);
    free(*pG);
    *pG = NULL;
}

/*** Access functions ***/

/* Returns the order */
int getOrder(Graph G){
    if(G == NULL){
        printf("Graph Error: calling getOrder() on NULL Graph reference\n");
        exit(1);
    }
    return G->order;
}

/* Returns the size */
int getSize(Graph G){
    if(G == NULL){
        printf("Graph Error: calling getSize() on NULL Graph reference\n");
        exit(1);
    }
    return G->size;
}

/* Returns the source vertex most recently used in function BFS(), or NIL if
BFS() has not yet been called */
int getSource(Graph G){
    if(G == NULL){
        printf("Graph Error: calling getSource() on NULL Graph reference\n");
        exit(1);
    }
    return G->source;
}

/* Will return the parent of vertex u in the Breadth- First tree created by
BFS(), or NIL if BFS() has not yet been called */
//Precondition 1 <= u <= getOrder(G)
int getParent(Graph G, int u){
    if(G == NULL){
        printf("Graph Error: calling getParent() on NULL Graph reference\n");
        exit(1);
    }
    if(u < 1 || u > getOrder(G)){
        printf("Graph Error: calling getParent() on out of bounds u\n");
        exit(1);
    }
    return G->parent[u];
}

/*Returns the distance from the most recent BFS source to vertex u,or INF if
BFS() has not yet been called */
//Precondition 1 <= u <= getOrder(G)
int getDist(Graph G, int u){
    if(G == NULL){
        printf("Graph Error: calling getDist() on NULL Graph reference\n");
        exit(1);
    }
    if(u < 1 || u > getOrder(G)){
        printf("Graph Error: calling getDist() on out of bounds u\n");
        exit(1);
    }
    if(getSource(G) == NIL){
        return INF;
    }
    return G->distance[u];
}

/*Appends to the List L the vertices of a shortest path in G from source to u,
or appends to L the value NIL if no such path exists */
//Precondition getSource(G)!=NIL, so BFS() must be called before getPath()
//Precondition 1 <= u <= getOrder(G)
void getPath(List L, Graph G, int u){
    if(G == NULL){
        printf("Graph Error: calling getPath() on NULL Graph reference\n");
        exit(1);
    }
    if(getSource(G) == NIL){
        printf("Graph Error: calling getPath() on NIL Source\n");
        exit(1);
    }
    if(u < 1 || u > getOrder(G)){
        printf("Graph Error: calling getPath() on out of bounds u\n");
        exit(1);
    }
    if(getSource(G) == u){
        append(L, getSource(G));
    }
    else if(G->parent[u] == NIL){
        append(L, NIL);
    }
    else{
        getPath(L, G, G->parent[u]);
        append(L, u);
    }
}

/*** Manipulation procedures ***/

/*Deletes all edges of G, restoring it to its original (no edge) state. (This
is called a null graph in graph theory literature) */
void makeNull(Graph G){
    if(G == NULL){
        printf("Graph Error: calling makeNULL() on NULL Graph reference\n");
        exit(1);
    }
    for(int i = 1; i <= getOrder(G); i++){
        clear(G->neighbors[i]);
    }
    G->size = 0;
}

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

/*Inserts a new edge joining u to v, i.e. u is added to the adjacency List of v,
and v to the adjacency List of u */
//Precondition that their 2 int arguments must lie in the range 1 to getOrder(G)
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

/*Inserts a new directed edge from u to v, i.e. v is added to the adjacency
List of u (but not u to the adjacency List of v) */
//Precondition that their 2 int arguments must lie in the range 1 to getOrder(G)
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

/*Runs the BFS algorithm on the Graph G with source s, setting the color,
distance, parent, and source fields of G accordingly */
void BFS(Graph G, int s){
    if(G == NULL){
        printf("Graph Error: calling BFS() on NULL Graph reference\n");
        exit(1);
    }
    if(s < 1 || s > getOrder(G)){
        printf("Graph Error: calling BFS() on out of bounds s\n");
        exit(1);
    }
    for(int i = 1; i <= getOrder(G); i++) {
        G->color[i] = WHITE;
        G->distance[i] = INF;
        G->parent[i] = NIL;
    }
    G->color[s] = GRAY;
    G->distance[s] = 0;
    G->parent[s] = NIL;
    G->source = s;

    List temp = newList();
    append(temp, s);
    while(length(temp) > 0){
        int x = front(temp);
        deleteFront(temp);
        List neighbors = G->neighbors[x];
        for(moveFront(neighbors); index(neighbors) != -1; moveNext(neighbors)){
            int y = get(neighbors);
            if(G->color[y] == WHITE){
                G->color[y] = GRAY;
                G->distance[y] = G->distance[x] + 1;
                G->parent[y] = x;
                append(temp, y);
            }
        }
        G->color[x] = BLACK;
    }
    freeList(&temp);
}

/*** Other operations ***/

//Prints the adjacency list representation of G to the file pointed to by out
void printGraph(FILE* out, Graph G){
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
