/* Yanling Wang Fall 2018 */
#include <stdio.h>
#include <stdlib.h>
#include "doublylinkedlist.h"

void insertHead(doublyLinkedList *listPtr, int value) {
  listNode *ins_h = (listNode*)malloc(sizeof(listNode));
  if (listPtr->head == NULL || listPtr->tail == NULL){  //empty list 
	ins_h->value = value;
	ins_h->next = NULL;
        ins_h->prev = NULL;
	listPtr->head = ins_h;
	listPtr->tail = ins_h;
  }
	
  else{							//Non-empty lsit
	listNode *temp = listPtr->head;
        ins_h->value = value;
	ins_h->next = temp;
	ins_h->prev = NULL;
	temp->prev = ins_h;
	listPtr->head = ins_h;
  } 
  return;
}

int removeTail(doublyLinkedList *listPtr) {
  int c = listPtr->tail->value;                         //value to remove
  if (listPtr->head == NULL || listPtr->tail == NULL){
	return;                                         //if list is empty
  }

  else if(listPtr->head == listPtr->tail){              //if only one element in list
 	listNode *temp = listPtr->tail;
        listPtr->head = NULL;
	listPtr->tail = NULL;
	free(temp);
  }

  else{                                                 //more than on element
	listNode *temp = listPtr->tail;
	temp->prev->next = NULL;
        listPtr->tail = temp->prev;
        free(temp);
  }

  return c;
} 

void showHead(doublyLinkedList *listPtr) {
  listNode *head = listPtr->head;
  printf("list head: ");
  while (head != NULL) {
    printf("%d ", head->value);
    head = head->next;
  } 
  printf("nil\n");
  return;
} 
void showTail(doublyLinkedList *listPtr) {
  listNode *tail = listPtr->tail;
  printf("list tail: ");
  while (tail != NULL) {
    printf("%d ", tail->value);
    tail = tail->prev; 
  } 
  printf("nil\n");
  return;
} 
void freeList(doublyLinkedList *listPtr) { 
  listNode *head = listPtr->head;
  listNode *temp;
  while(head != NULL) {
    temp = head->next;
    free(head);
    head = temp;
  }
  listPtr->head = NULL;
  listPtr->tail = NULL;
  return;
}

