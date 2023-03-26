#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 256

int stack[MAX_SIZE];
int top = -1;

bool isFull() { return top == MAX_SIZE - 1; }

bool isEmpty() { return top == -1; }

void push(int x) {
  if (isFull()) {
    printf("stack overflow\n");
    exit(1);
  }
  stack[++top] = x;
}

int pop() {
  if (isEmpty()) {
    printf("stack underflow\n");
    exit(1);
  }
  return stack[top--];
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
  switch (operator) {
  case '+':
    return true;
  case '-':
    return true;
  case '*':
    return true;
  case '/':
    return true;
  }
}

int evaluate(int num1, char operator, int num2) {
  switch (operator) {
  case '+':
    return num1 + num2;
  case '-':
    return num1 - num2;
  case '*':
    return num1 * num2;
  case '/':
    return num1 / num2;
  }
}

void postfixEvaluator(struct Node *head) {
  struct Node *current = head;
  while (current != NULL) {
    if (isalnum(*current->data) ||
        (current->data[0] == '-' && strlen(current->data) > 1)) {
      int num = atoi(current->data);
      push(num);
    } else if (isOperator(*current->data)) {
      int num2 = pop();
      int num1 = pop();
      push(evaluate(num1, *current->data, num2));
    }
    current = current->next;
  }
  printf("Output: %d\n", pop());
}

int main() {
  struct Node *head = NULL;
  char input[MAX_SIZE];
  char tempString[MAX_SIZE];

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
