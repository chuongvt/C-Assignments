/* Chuong Viet Truong
 * Chvtruon
 * CMPS 101
 * PA 2
 */

#include <stdio.h>
#include <stdlib.h>
#include "List.h"

typedef struct NodeObj{
    int data;
    struct NodeObj* next;
    struct NodeObj* prev;
}NodeObj;

typedef NodeObj* Node;

typedef struct ListObj{
    Node front;
    Node back;
    Node cursor;
    int length;
    int cursorIndex;
}ListObj;

// Constructors-Destructors

Node newNode(int data){
    Node N = malloc(sizeof(NodeObj));
    N->data = data;
    N->next = N->prev = NULL;
    return(N);
}

void freeNode(Node* pN){
    if(pN != NULL && *pN != NULL){
        free(*pN);
        *pN = NULL;
    }
}

List newList(void){
    List L;
    L = malloc(sizeof(ListObj));
    L->front = L->back = NULL;
    L->cursor = NULL;
    L->length = 0;
    L->cursorIndex = -1;
    return(L);
}

void freeList(List* pL) {
    if(pL != NULL && *pL != NULL){
        while(length(*pL)>0){
            deleteFront(*pL);
        }
        free(*pL);
        *pL = NULL;
    }
}

// Access Functions

int length(List L){
    if(L == NULL){
        printf("List Error: calling front() on NULL List reference\n");
        exit(1);
    }
    return(L->length);
}

int index(List L){
    if(L == NULL){
		printf("List Error: calling index() on NULL List reference\n");
		exit(1);
	}
    if(L->cursor == NULL){
        L->cursorIndex = -1;
        return (L->cursorIndex);
    }
    return(L->cursorIndex);
}

int front(List L){
    if(L == NULL){
        printf("List Error: calling front() on NULL List reference\n");
        exit(1);
    }
    if(L->length == 0){
        printf("List Error: calling front() on an empty List\n");
        exit(1);
    }
    return(L->front->data);
}

int back(List L){
    if(L == NULL){
        printf("List Error: calling back() on NULL List reference\n");
        exit(1);
    }
    if(L->length == 0){
        printf("List Error: calling back() on an empty List\n");
        exit(1);
    }
    return(L->back->data);
}

int get(List L){
    if(L == NULL){
        printf("List Error: calling get() on NULL List reference\n");
        exit(1);
    }
    if(L->length == 0){
        printf("List Error: calling get() on an empty List\n");
        exit(1);
    }
    if(L->cursorIndex == -1) {
        printf("List Error: calling get() on NULL cursor reference\n");
        exit(1);
    }
    return(L->cursor->data);
}

int equals(List A, List B){
    int flag = 0;

    if(A == NULL || B == NULL){
        printf("List Error: calling equals() on NULL List reference\n");
    }

    flag = (A->length == B->length);
    Node N = A->front;
    Node M = B->front;
    while(flag && N!=NULL){
    flag = (N->data == M->data);
        N = N->next;
        M = M->next;
    }
    return flag;
}

// Manipulation Procedures

void clear(List L){
    if(L == NULL) {
        printf("List Error: calling clear() on NULL List reference\n");
        exit(1);
    }
    Node N = L->front;
    while(N != NULL){
        N = N->next;
        deleteFront(L);
    }

    L->front = L->back = L->cursor = NULL;
    L->length = 0;
    L->cursorIndex = -1;
}

void moveFront(List L){
    if(L == NULL) {
        printf("List Error: calling moveFront() on NULL List reference\n");
        exit(1);
    }
    if(length(L) > 0){
        L->cursor = L->front;
        L->cursorIndex = 0;
    }
}

void moveBack(List L){
    if(L == NULL) {
        printf("List Error: calling moveBack() on NULL List reference\n");
        exit(1);
    }
    if(length(L) > 0){
        L->cursor = L->back;
        L->cursorIndex = length(L) - 1;
    }
}

void movePrev(List L){
    if(L == NULL) {
        printf("List Error: calling movePrev() on NULL List reference\n");
        exit(1);
    }
    if(L->cursor == L->front){
        L->cursor = NULL;
        L->cursorIndex = -1;
    }
    else{
        L->cursor = L->cursor->prev;
        L->cursorIndex--;
    }
}

void moveNext(List L){
    if(L == NULL) {
        printf("List Error: calling moveNext() on NULL List reference\n");
        exit(1);
    }
    if(L->cursor == L->back){
        L->cursor = NULL;
        L->cursorIndex = -1;
    }
    else{
        L->cursor = L->cursor->next;
        L->cursorIndex++;
    }
}

void prepend(List L, int data){
    Node N = newNode(data);
    if(length(L) == 0){
        L->front = L->back = N;
    }
    else{
        N->next = L->front;
        L->front->prev = N;
        L->front = L->front->prev;
    }
    L->length++;
    if(index(L) != -1){
        L->cursorIndex++;
    }
}

void append(List L, int data){
    Node N = newNode(data);
    if(length(L) == 0){
        L->front = L->back = N;
    }
    else{
        N->prev = L->back;
        L->back->next = N;
        L->back = L->back->next;
    }
    L->length++;
}

void insertBefore(List L, int data){
    if(L == NULL) {
        printf("List Error: calling insertBefore() on NULL List reference\n");
        exit(1);
    }
    if(length(L) == 0) {
        printf("List Error: calling insertBefore() on empty List\n");
        exit(1);
    }
    if(index(L) == -1) {
        printf("List Error: calling insertBefore() with undefined cursor\n");
        exit(1);
    }
    if(index(L) == 0){
        prepend(L, data);
    }
    else {
        Node N = newNode(data);
        N->next = L->cursor;
        N->prev = L->cursor->prev;
        L->cursor->prev->next = N;
        L->cursor->prev = N;
        L->cursorIndex++;
        L->length++;
    }
}

void insertAfter(List L, int data){
    if(L == NULL) {
        printf("List Error: calling insertAfter() on NULL List reference\n");
        exit(1);
    }
    if(length(L) == 0) {
        printf("List Error: calling insertAfter() on empty List\n");
        exit(1);
    }
    if(index(L) == -1) {
        printf("List Error: calling insertAfter() with undefined cursor\n");
        exit(1);
    }
    if(index(L) == length(L)-1){
        append(L, data);
    }
    else{
        Node N = newNode(data);
        N->prev = L->cursor;
        N->next = L->cursor->next;
        L->cursor->next->prev = N;
        L->cursor->next = N;
        L->length++;
    }
}

void deleteFront(List L){
    if(L == NULL) {
        printf("List Error: calling deleteFront() on NULL List reference\n");
        exit(1);
    }
    if(length(L) == 0) {
        printf("List Error: calling deleteFront() on empty List\n");
        exit(1);
    }
    Node N = L->front;

    if(length(L) > 0){
        if(length(L) == 1){
            L->front = NULL;
            L->back = NULL;
        }
        else{
            L->front = L->front->next;
            L->front->prev = NULL;
        }
        if(index(L) != -1){
            L->cursorIndex--;
        }
        L->length--;
        freeNode(&N);
    }
}

void deleteBack(List L){
    if(L == NULL) {
        printf("List Error: calling deleteBack() on NULL List reference\n");
        exit(1);
    }
    if(length(L) == 0) {
        printf("List Error: calling deleteBack() on empty List\n");
        exit(1);
    }
    Node N = L->back;

    if(length(L) > 0){
        if(length(L) == 1){
            L->front = NULL;
            L->back = NULL;
        }
        else{
            L->back = L->back->prev;
            L->back->next = NULL;
        }
        if(index(L) == length(L)-1){
            L->cursorIndex = -1;
        }
        L->length--;
        freeNode(&N);
    }
}

void delete(List L){
    if(L == NULL) {
        printf("List Error: calling delete() on NULL List reference\n");
        exit(1);
    }
    if(length(L) == 0) {
        printf("List Error: calling delete() on empty List\n");
        exit(1);
    }
    if(index(L) == -1) {
        printf("List Error: calling delete() with undefined cursor\n");
        exit(1);
    }
    if(index(L)>=0 && length(L)>0) {
        if(index(L)==0) {
            deleteFront(L);
        }
        else if (index(L)==length(L)-1) {
            deleteBack(L);
        }
        else {
            Node N = L->cursor;
            Node after = L->cursor->next;
            Node before = L->cursor->prev;
            before->next = after;
            after->prev = before;
            L->length--;
            L->cursor = NULL;
            L->cursorIndex = -1;
            freeNode(&N);
        }
    }
}

// Other Operations

void printList(FILE* out, List L){
    Node N = NULL;

    if(L == NULL) {
        printf("List Error: calling printList() on NULL List reference\n");
        exit(1);
    }

    for (N = L->front; N != NULL; N = N->next){
        fprintf(out, "%d ", N->data);
    }
}

List copyList(List L){
    if(L == NULL) {
        printf("List Error: calling printList() on NULL List reference\n");
        exit(1);
    }

    List copy = newList();
    Node N = L->front;
    while(N != NULL){
        append(copy, N->data);
        N = N->next;
    }

    copy->length = length(L);
    return copy;
}
