/* Chuong Viet Truong
 * Chvtruon
 * CMPS 101
 * PA 5
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "List.h"
#include "Graph.h"


int main(int argc, char* argv[]){
    int v1, v2;
    int n = 0;
    int sccCount = 0;
    FILE *in, *out;

    if(argc != 3){
        printf("Usage: %s <input file> <output file>\n", argv[0]);
        exit(1);
    }

    // Open input & output file
    in = fopen(argv[1], "r");
    out = fopen(argv[2], "w");
    if(in == NULL){
       printf("Unable to open file %s for reading\n", argv[1]);
       exit(1);
    }
    if(out == NULL){
       printf("Unable to open file %s for writing\n", argv[2]);
       exit(1);
    }

    // Read # of vertices from input & makes graph
    fscanf(in, "%d", &n);
    Graph G = newGraph(n);

    // Scans through the file and stores vertices
    while(fgetc(in) != EOF){
        fscanf(in, "%d", &v1);
        fscanf(in, "%d", &v2);
        if(v1 == 0 && v2 == 0){
            break;
        }
        addArc(G, v1, v2);
    }

    // Print graph
    fprintf(out, "Adjacency list representation of G:\n");
    printGraph(out, G);
    fprintf(out, "\n");

    // Inserts vertices into a List
    List L = newList();
    for(int i = 1; i <= n; i++){
        append(L, i);
    }

    // Run DFS
    DFS(G, L);

    // Transpose graph
    Graph transposedG = transpose(G);

    // Run DFS on transposed graph
    DFS(transposedG, L);

    // Count SCC's in graph & print
    for(int i = 1; i <= getOrder(transposedG); i++){
        if(getParent(transposedG, i) == NIL){
            sccCount++;
        }
    }
    fprintf(out, "G contains %d strongly connected components:\n", sccCount);

    // Create a list to store scc's
    List* sccList = calloc(sccCount+1, sizeof(List));
    for(int i = 1; i <= sccCount; i++){
        sccList[i] = newList();
    }

    // Finds scc
    for(int i = 1; i <= sccCount; i++){
        while(getParent(transposedG, back(L)) != NIL){
            prepend(sccList[i], back(L));
            deleteBack(L);
        }
        if(getParent(transposedG, back(L)) == NIL){
            prepend(sccList[i], back(L));
            deleteBack(L);
        }
    }

    for(int i = 1; i <= sccCount; i++){
        fprintf(out, "Component %d:", i);
        printList(out, sccList[i]);
        fprintf(out, "\n");
    }

    for(int i = 0; i <= sccCount; i++){
		freeList(&sccList[i]);
	}
    free(sccList);
    freeGraph(&G);
    freeGraph(&transposedG);
    freeList(&L);
    fclose(in);
    fclose(out);
    return 0;
}
