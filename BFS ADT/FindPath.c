/* Chuong Viet Truong
 * Chvtruon
 * CMPS 101
 * PA 4
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "List.h"
#include "Graph.h"

int main(int argc, char* argv[]){
    int v1, v2, source, destination;
    int n = 0 ;
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
        addEdge(G, v1, v2);
    }

    // Print vertices w/ adjacency list representations
    printGraph(out, G);
    fprintf(out, "\n");

    // Perform BFS
    while(fgetc(in) != EOF){
        fscanf(in, "%d", &source);
        fscanf(in, "%d", &destination);
        if (source == 0 && destination == 0){
            break;
        }
        List list = newList();
        BFS(G, source);
        getPath(list, G, destination);
        if (getDist(G, destination) != INF){
            fprintf(out, "The distance from %d to %d is %d\n", source, destination, length(list) - 1);
            fprintf(out, "A shortest %d-%d path is: ", source, destination);
            printList(out, list);
            fprintf(out, "\n\n");
        }
        else{
            fprintf(out, "The distance from %d to %d is infinity\n", source, destination);
            fprintf(out, "No %d-%d path exists\n", source, destination);
            fprintf(out, "\n");
        }
        freeList(&list);
    }

    // Free graph & close files
    freeGraph(&G);
    fclose(in);
    fclose(out);
}
