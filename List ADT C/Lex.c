/* Chuong Viet Truong
 * Chvtruon
 * CMPS 101
 * PA 2
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "List.h"

#define MAX_LEN 200

int main(int argc, const char * argv[]) {
    FILE *in, *out;
    int n = 0, lineCount = 0;
    char line[MAX_LEN];
    char *wordList[MAX_LEN];

    if(argc != 3){
        printf("Usage: %s <input file> <output file>\n", argv[0]);
        exit(1);
    }

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
    while(fgets(line, MAX_LEN, in) != NULL) {
        lineCount++;
    }
    rewind(in);

    for(int i=0; i<lineCount; i++){
        wordList[i] = (char *)malloc(MAX_LEN);
    }
    while(fgets(line, MAX_LEN, in) != NULL){
        strcpy(wordList[n], line);
        n++;
    }

    List list = newList();
    append(list, 0);
    for(int i=1; i<lineCount; i++){
        char *t = wordList[i];
        moveBack(list);
        int j = i - 1;
        while(j>=0 && strcmp(t, wordList[get(list)]) <= 0 ){
            movePrev(list);
            j--;
        }
        if(index(list) >= 0){
            insertAfter(list, i);
        }
        else{
            prepend(list, i);
        }
    }

    moveFront(list);
    while(index(list)>=0){
        fprintf(out, "%s", wordList[get(list)]);
        moveNext(list);
    }

    fclose(in);
    fclose(out);

    for(int i=0; i<lineCount; i++){
        free(wordList[i]);
    }
    freeList(&list);
    return 0;
}
