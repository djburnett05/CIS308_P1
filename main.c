/**********************************************
* Name: David J Burnett
* Date: 09.19.2025
* Assignment: Project 1 - Sequence and Order validation *
***********************************************
* This program reads a list of expressions from a file
* and checks if the parentheses, brackets, and braces in each
* expression are balanced.
* The checking is done with a stack struct and implements
* push, pop, and peek.
* The program outputs whether each expression 
* is correct or incorrect.
***********************************************/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STRING_LENGTH 26  // 25 chars + 1 for null terminator

/**********************************************
* Struct: Stack 
* Description: A stack data structure to hold characters.
* contains top indexer, size, and char array.
* Input: N/A
* Output: N/A
************************************************/
struct Stack
{
    int top;
    int size;
    char* arr;
};

//---------------------------FUNCTION PROTOTYPES---------------------------//
// See functions for comments.

struct Stack* createStack(int size);
void push(struct Stack* stack, char c);
char peek(struct Stack* stack);
char pop(struct Stack* stack);

int validateExpression(char expression[]);


//---------------------------MAIN---------------------------//

int main()
{
    // Open the file for reading.
    FILE *fp = fopen("expressions.txt", "r");
    if(fp == NULL)
    {
        printf("Error: File was not opened\n");
        return 1;
    }

    // A bool flag to check if we are on the first line.
    int firstline = 1;

    // A character array for the expression, max length of 25 (+1 for terminator).
    char expression[MAX_STRING_LENGTH];

    // While there are more expressions in the file...
    while(fscanf(fp, "%s", expression) != EOF)
    {
        // If we are on the first line...
        if(firstline)
        {
            // Store the value on the first line and check if it is greater than 10.
            int foo = atoi(expression);
            if(foo > 10)
            {
                printf("Error: File size too large (%d)\n", foo);
                return 1;
            }
            // Clear the firstline flag.
            firstline = 0;
        }
        else
        {
            validateExpression(expression);
        }
        
    }


    return 0;
}

//-------------------------END MAIN-------------------------//

/**********************************************
 * Function: createStack
* Description: Creates a stack with the given size.
* Input: int size - the size of the stack.
* Output: struct Stack* - pointer to the created stack.
***********************************************/
struct Stack* createStack(int size)
{
    // Allocate the heap space for a stack.
    struct Stack* stack = malloc(sizeof(struct Stack));
    
    // Initialize the size of the stack.
    stack->size = size;
    // Sets to -1 to show stack is empty.
    stack->top = -1; 

    stack->arr = malloc(size *sizeof(int));

    return stack;
}

/**********************************************
* Function: push
* Description: pushes the given character onto the given stack.
* Input: struct Stack* stack - pointer to the stack.
*        char c - character to push onto the stack.
* Output: void
***********************************************/
void push(struct Stack* stack, char c)
{
    if(stack->top < stack->size)
    {
        stack->top++;
        stack->arr[stack->top] = c;
    }
    else
    {
        printf("Stack Overflow\n");
    }
}
/**********************************************
* Function: peek
* Description: returns the top character of the stack without removing it.
* Input: struct Stack* stack - pointer to the stack.
* Output: char - the top character of the stack.
***********************************************/
char peek(struct Stack* stack)
{
    if(stack->top != -1)
    {
        return stack->arr[stack->top];
    }
    else
    {
        printf("Stack is empty\n");
        return '\0';
    }
}

/**********************************************
* Function: pop
* Description: removes and returns the top character of the stack.
* Input: struct Stack* stack - pointer to the stack. 
* Output: char - the top character of the stack.
***********************************************/
char pop(struct Stack* stack)
{
    if(stack->top != -1)
    {
        char c = stack->arr[stack->top];
        stack->top--;
        return c;
    }
    else
    {
        printf("Stack Underflow\n");
        return '\0';
    }
}

/**********************************************
* Function: validateExpression
* Description: Validates if the given expression has 
* balanced parentheses, brackets, and braces.
* Input: char expression[] - the expression to validate.
* Output: int - 1 if the expression is balanced, 0 otherwise.
* OFNOTE: The return value is currently unused. May be useful
* as a boolean check if preferred.
***********************************************/
int validateExpression(char expression[])
{
    // Get the length of the expression.
    int length = strlen(expression);
    int balanced = 1;
    // Create a stack with a size equal to the length of the expression.
    struct Stack* stack = createStack(length);

    // Loop through each character in the expression.
    for(int i = 0; i < length; i++)
    {
        balanced = 1;
        char c = expression[i];

        // If the character is an opening parinthesis, curly bracket, or bracket, push it onto the stack.
        if(c == '(' || c == '{' || c == '[')
        {
            push(stack, c);
        }
        // If the character is a closing parinthesis, curly bracket, or bracket, check if it matches the top of the stack.
        else if(c == ')' || c == '}' || c == ']')
        {
            char top = peek(stack);
            if((c == ')' && top == '(') || (c == '}' && top == '{') || (c == ']' && top == '['))
            {
                pop(stack); // Pop the matching opening bracket off the stack.
            }
            else
            {
                // If it doesn't match, the expression is unbalanced.
                printf("%s --> Incorrect \n", expression);
                balanced = 0;
                break;
            }
        }
        else
        {
            // If the character is not a bracket, the expression is invalid.
            printf("Invalid character in expression: %s\n", expression);
            break;
        }
    }

    // If the expression is balanced and the stack is empty, it is valid.
    if(balanced && stack->top == -1)
    {
        printf("%s --> Correct \n", expression);
    }

     // Free the stack memory.
    free(stack->arr);
    free(stack);
}