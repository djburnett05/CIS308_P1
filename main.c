#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// A struct for a stack. A stack has top
struct Stack
{
    int top;
    int size;
    int* arr;
};

struct Stack* createStack(int size);
void push(struct Stack* stack, char c);
char peek(struct Stack* stack);
char pop(struct Stack* stack);

//---------------------------MAIN---------------------------//

int main()
{

}

//-------------------------END MAIN-------------------------//

// Creates a new stack of length size.
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

// WORK HERE
void push(struct Stack* stack, char c)
{
    if(stack->top < stack->size)
    {
        stack->top++;
        
    }
}

char peek(struct Stack* stack)
{

}

char pop(struct Stack* stack)
{

}