/* Yanling Wang Fall 2018 */
#include <stdio.h>
#include <string.h>
#include "doublylinkedlist.h"
#define MAXLINE 100
void printHelp() {
  printf("help -- print this message.\n");
  printf("insert n -- insert value n to the head of the list.\n");
  printf("remove --  remove the tail of the list and print its value.\n");
  printf("showhead -- show the whole list from head.\n");
  printf("showtail -- show the whole list from tail.\n");
  printf("freelist -- free the whole list and set the list to NULL.\n");
  printf("quit -- quit the program and free the whole list.\n");
}
int main() {
  char command[20];
  char commandline[MAXLINE];
  doublyLinkedList list = {NULL, NULL};
  int value;
  int argcount;
  printf("List driver, enter help for help.\ncommand>");
  while (fgets(commandline, MAXLINE, stdin)) {
    sscanf(commandline, "%19s", command);
    if (!strcmp(command, "help")) {
      printHelp();
    }
    else if (!strcmp(command, "insert")) {
      argcount = sscanf(commandline, "%19s %d", command, &value);
      if (argcount == 2) {
        insertHead(&list, value);
      }
      else {
        printf("Invalid argument for insert.\n");
      }
    }
    else if (!strcmp(command, "remove")) {
      if (list.head == NULL) {
        printf("Error in remove: empty list.\n");
      }
      else {
        value = removeTail(&list);
        printf("Removed tail value = %d\n", value);
      }
    }
    else if (!strcmp(command, "showhead")) {
      showHead(&list);
    }
    else if (!strcmp(command, "showtail")) {
      showTail(&list);
    }
    else if (!strcmp(command, "freelist")) {
      freeList(&list);
    }
    else if (!strcmp(command, "quit")) {
      break;
    }
    else {
      printf("Invalid command.\n");
    }
    printf("command>");
  }
  freeList(&list);
  printf("Good bye.\n");
  return 0;
} 
