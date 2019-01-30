/* Yanling Wang Fall 2018 */
#ifndef LIST_H
#define LIST_H
typedef struct listNode {
  int value;
  struct listNode *next;
} listNode;
void displayList(listNode *list); 
void push(listNode **listPtr, int value);
int pop(listNode **listPtr); 
void destroyList(listNode **listPtr); 
void reverse(listNode **listPtr);
void insert(listNode **listPtr, int value);
void removeAll(listNode **listPtr, int value);
int count(listNode *listPtr, int value); 

#endif //LIST_H
