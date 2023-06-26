#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 256

int stack[MAX_SIZE];
int top = -1;

bool isFull()
{
    return top == MAX_SIZE - 1;
}

bool isEmpty()
{
    return top == -1;
}

void push(int x)
{
    if (isFull())
    {
        printf("stack overflow\n");
        exit(1);
    }
    stack[++top] = x;
}

int pop()
{
    if (isEmpty())
    {
        printf("stack underflow\n");
        exit(1);
    }
    return stack[top--];
}

typedef struct node
{
    char *data;
    struct node *next;
} node;

void addNode(node **head, char *data)
{
    node *newNode = malloc(sizeof(node));
    newNode->data = malloc(strlen(data));
    strcpy(newNode->data, data);
    newNode->next = NULL;

    if (*head == NULL)
    {
        *head = newNode;
    }
    else
    {
        node *current = *head;
        while (current->next != NULL)
        {
            current = current->next;
        }
        current->next = newNode;
    }
}

bool isOperator(char operator)
{
    switch (operator)
    {
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

int evaluate(int num1, char operator, int num2)
{
    switch (operator)
    {
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

void postfixEvaluator(node *head)
{
    node *current = head;
    while (current != NULL)
    {
        if (isalnum(*current->data) || (current->data[0] == '-' &&
                                        strlen(current->data) > 1))
        {
            int num = atoi(current->data);
            push(num);
        }
        else if (isOperator(*current->data))
        {
            int num2 = pop();
            int num1 = pop();
            push(evaluate(num1, *current->data, num2));
        }
        current = current->next;
    }
    printf("Output: %d\n", pop());
}

int main()
{
    node *head = NULL;
    char input[MAX_SIZE];
    char tempString[MAX_SIZE];

    printf("input: ");
    fgets(input, MAX_SIZE, stdin);

    int index1 = 0;
    int index2 = 0;
    while (input[index1] != '\0')
    {
        if (isspace(input[index1]))
        {
            tempString[index2++] = '\0';
            addNode(&head, tempString);
            index2 = 0;
        }
        else
        {
            tempString[index2++] = input[index1];
        }
        index1++;
    }

    postfixEvaluator(head);
    return 0;
}
