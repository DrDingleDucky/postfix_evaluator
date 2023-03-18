#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>

#define MAX_SIZE 256

int intStack[MAX_SIZE];
int intTop = -1;

bool isFull(int *top)
{
    return *top == MAX_SIZE;
}

bool isEmpty(int *top)
{
    return *top == -1;
}

void pushInt(int stack[], int *top, int x)
{
    if (isFull(top))
    {
        printf("there is not space left in the stack\n");
        exit(1);
    }
    stack[++*top] = x;
}

int popInt(int stack[], int *top)
{
    if (isEmpty(top))
    {
        printf("nothing to take from the stack\n");
        exit(1);
    }
    return intStack[(*top)--];
}

void removeSpaces(char string[])
{
    int i, j;
    for (i = 0, j = 0; i < strlen(string); i++)
    {
        if (string[i] != ' ')
        {
            string[j++] = string[i];
        }
    }
    string[j] = '\0';
}

bool isOperator(char operator)
{
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

int evaluator(int num1, char operator, int num2)
{
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

void postfixEvaluator(char inputString[])
{
    char token;
    int i;
    for (i = 0; i < strlen(inputString); i++)
    {
        token = inputString[i];

        if (isdigit(token))
        {
            int num = atoi(&token);
            pushInt(intStack, &intTop, num);
        }
        else if (isOperator(token))
        {
            int num2 = popInt(intStack, &intTop);
            int num1 = popInt(intStack, &intTop);
            pushInt(intStack, &intTop, evaluator(num1, token, num2));
        }
    }
    printf("%d\n", popInt(intStack, &intTop));
}

int main()
{
    char inputString[MAX_SIZE];

    printf("enter a postfix expression: ");
    fgets(inputString, MAX_SIZE, stdin);

    removeSpaces(inputString);

    printf("input: %s", inputString);

    postfixEvaluator(inputString);

    return 0;
}
