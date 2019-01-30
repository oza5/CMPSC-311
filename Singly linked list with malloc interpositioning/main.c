/* Yanling Wang Fall 2018 */
#include <stdio.h>
#include <string.h>
#include "list.h"
#define MAXLINE 100
void printHelp() {
  printf("help -- print this message.\n");
  printf("push n -- push value n to the beginning of the list.\n");
  printf("pop --  pop the head of the list and print its value.\n");
  printf("show -- show the whole list.\n");
  printf("reverse -- reverse the list (without any malloc/free).\n");
  printf("insert n -- add value n to the end of the list.\n");
  printf("count n -- count how many times value n appeared in the list.\n");
  printf("remove n -- remove all nodes with value n from the list.\n");
  printf("quit -- quit the program and destroy the whole list.\n");
}
int main() {
  char command[20];
  char commandline[MAXLINE];
  listNode *list = NULL;
  int value;
  int argcount;
  int valuecount;
  printf("List driver, enter help for help.\ncommand>");
  while (fgets(commandline, MAXLINE, stdin)) {
    sscanf(commandline, "%19s", command);
    if (!strcmp(command, "help")) {
      printHelp();
    }
    else if (!strcmp(command, "push")) {
      argcount = sscanf(commandline, "%19s %d", command, &value);
      if (argcount == 2) {
        push(&list, value);
      }
      else {
        printf("Invalid argument for push.\n");
      }
    }
    else if (!strcmp(command, "pop")) {
      if (list == NULL) {
        printf("Error in pop: empty list.\n");
      }
      else {
        value = pop(&list);
        printf("Popped value = %d\n", value);
      }
    }
    else if (!strcmp(command, "show")) {
      displayList(list);
    }
    else if (!strcmp(command, "reverse")) {
      reverse(&list);
    }
    else if (!strcmp(command, "insert")) {
      argcount = sscanf(commandline, "%19s %d", command, &value);
      if (argcount == 2) {
        insert(&list, value);
      }
      else {
        printf("Invalid argument for insert.\n");
      }
    }
    else if (!strcmp(command, "remove")) {
      argcount = sscanf(commandline, "%19s %d", command, &value);
      if (argcount == 2) {
        removeAll(&list, value);
      }
      else {
        printf("Invalid argument for remove.\n");
      }
    }
    else if (!strcmp(command, "count")) {
      argcount = sscanf(commandline, "%19s %d", command, &value);
      if (argcount == 2) {
        valuecount = count(list, value);
        printf("Value %d appeared %d times.\n", value, valuecount);
      }
      else {
        printf("Invalid argument for count.\n");
      }
    }
    else if (!strcmp(command, "quit")) {
      break;
    }
    else {
      printf("Invalid command.\n");
    }
    printf("command>");
  }
  destroyList(&list);
  printf("Good bye.\n");
  return 0;
} 
