/* Yanling Wang Fall 2018 */
#ifndef LIST_H
#define LIST_H
typedef struct listNode {
  int value;
  struct listNode *next;
  struct listNode *prev;
} listNode;

typedef struct doublyLinkedList {
  listNode *head;
  listNode *tail;
} doublyLinkedList;


void insertHead(doublyLinkedList *listPtr, int value);
int removeTail(doublyLinkedList *listPtr); 
void showHead(doublyLinkedList *listPtr);
void showTail(doublyLinkedList *listPtr);
void freeList(doublyLinkedList *listPtr);
#endif //LIST_H
