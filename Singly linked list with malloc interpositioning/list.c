/* Osman Ali Fall 2018 */
#include <stdio.h>
#include <stdlib.h>
#include "list.h"

/* print out the content of a list */
void displayList(listNode *list) {
  printf("list: ");
  while(list != NULL) {
    printf("%d ", list->value);
    list = list->next;
  }
  printf("%p\n", list);
  return;
}

/* given a pointer to the head of the list and a value,
 * add a new node with value to the head of the list */
void push(listNode **listPtr, int value) {
  listNode *newNodePtr = (listNode *)malloc(sizeof(listNode));
  newNodePtr->value = value;
  newNodePtr->next = *listPtr;
  *listPtr = newNodePtr;
  return;
}


/* remove the head of the list (and free its memory), and
 * return its value. If the list is empty, return 0 */ 
int pop(listNode **listPtr) {
  int value = 0;
  listNode *tempPtr;
  if (*listPtr) {
    tempPtr = *listPtr;
    value = tempPtr->value;
    *listPtr = tempPtr->next;
    free(tempPtr);
  }
  return value;
}


/* remove and free memory of all the element of the list. */
void destroyList(listNode **listPtr) {
  listNode *temp = *listPtr;
  while(temp != NULL) {
    *listPtr = (*listPtr) -> next;
    free(temp);
    temp = *listPtr;
  }
  return;
}


void reverse(listNode **listPtr) {
  listNode *prev = NULL;
  listNode *current = *listPtr;
  listNode *next;
  while (current != NULL){
	next = current -> next;
	current -> next = prev;
        prev = current;
	current = next;
	}
  *listPtr = prev;
}


void insert(listNode **listPtr, int value) {
  listNode *cursor = *listPtr;
  if (cursor == NULL){
 	push(listPtr,value);}
  else{
  while(cursor->next != NULL)
	cursor= cursor -> next;
  listNode *newNode = (listNode *)malloc(sizeof(listNode));
  newNode->value = value;
  newNode->next = NULL;
  cursor->next = newNode; }
}



void removeAll(listNode **listPtr, int value){
listNode *current = *listPtr;
listNode *cursor = *listPtr;
while(current != NULL){
  if (current-> value == value){
	//if the node is head
  	if (current == *listPtr){
		pop(listPtr);}
  	//if the node is tail	
	else if (current->next ==  NULL){
		listNode *cursor = *listPtr;
		listNode *back = NULL;
		while(cursor->next != NULL){
			back = cursor;
			cursor = cursor->next;}
		if(back!= NULL){
	  		back ->next = NULL;}
		if(cursor == *listPtr){
			*listPtr = NULL;}
		free(cursor);}
	//if node in middle
        else{  
		if (current->next != NULL){
			while(cursor->next != current){
			cursor = cursor->next;
			}
                        
			listNode *tmp = cursor->next;
			cursor->next = tmp->next;
			tmp->next = NULL;
			free(tmp);
			removeAll(listPtr,value);
			}
	}
   }
current = current->next;}
}


int count(listNode *listPtr, int value) {
  int c = 0;
  while (listPtr != NULL){
	if(listPtr->value == value){
		c+=1;}
	listPtr = listPtr -> next;} 
  return c;
} 
