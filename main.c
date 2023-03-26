#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 256

int stack[MAX_SIZE];
int top = 1;

bool isFull(int *top) { return *top == MAX_SIZE; }

bool isEmpty(int *top) { return *top == -1; }

void push(int stack[], int *top, int x) {
  if (isFull(top)) {
    printf("there is not space left in the stack\n");
    exit(1);
  }
  stack[++*top] = x;
}

int pop(int stack[], int *top) {
  if (isEmpty(top)) {
    printf("nothing to take from the stack\n");
    exit(1);
  }
  return stack[(*top)--];
}

struct Node {
  char *data;
  struct Node *next;
};

void addNode(struct Node **head, char *newData) {
  struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
  newNode->data = strdup(newData);
  newNode->next = NULL;

  if (*head == NULL) {
    *head = newNode;
  } else {
    struct Node *current = *head;
    while (current->next != NULL) {
      current = current->next;
    }
    current->next = newNode;
  }
}

bool isOperator(char operator) {
  if (operator== '+')
    return true;
  else if (operator== '-')
    return true;
  else if (operator== '*')
    return true;
  else if (operator== '/')
    return true;
  else
    return false;
}

int evaluator(int num1, char operator, int num2) {
  int result;
  if (operator== '+')
    return num1 + num2;
  else if (operator== '-')
    return num1 - num2;
  else if (operator== '*')
    return num1 * num2;
  else if (operator== '/')
    return num1 / num2;
}

int postfixEvaluator(struct Node *head) {
  struct Node *current = head;
  int i;
  while (current != NULL) {
    if (isalnum(*current->data) ||
        current->data[0] == '-' && strlen(current->data) != 1) {
      int num = atoi(current->data);
      push(stack, &top, num);
    } else if (isOperator(*current->data)) {
      int num2 = pop(stack, &top);
      int num1 = pop(stack, &top);
      push(stack, &top, evaluator(num1, *current->data, num2));
    }
    current = current->next;
  }
  printf("output: %d\n", pop(stack, &top));
}

int main() {
  struct Node *head = NULL;
  char input[MAX_SIZE];
  char tempString[16];

  printf("input: ");
  fgets(input, MAX_SIZE, stdin);

  int i = 0;
  int j = 0;
  while (input[i] != '\0') {
    if (isspace(input[i])) {
      tempString[j++] = '\0';
      addNode(&head, tempString);
      j = 0;
    } else {
      tempString[j++] = input[i];
    }
    i++;
  }

  postfixEvaluator(head);
  return 0;
}
