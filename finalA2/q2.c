#include "q2.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char** argv){

  Operand *stack = NULL;

    if (argc != 2) {
        printf("Usage: %s <expression>\n", argv[0]);
        return 1;
    }

    char *expr = argv[1];

  //Pointer to the stack
  /*int i = 0;
  Operand * stack = NULL;
  */


  //Loop through the second command line arguement, containing the operands and the numbers 

    for (int i = 0; i < strlen(expr); i++) {
        char ch = expr[i];
        if (ch >= '0' && ch <= '9') {
            push(&stack, ch - '0'); // Convert char to int
        } else {
            double b = pop(&stack);
            double a = pop(&stack);
            switch (ch) {
                case '+': push(&stack, a + b); break;
                case '-': push(&stack, a - b); break;
                case '*': push(&stack, a * b); break;
                case '/': push(&stack, a / b); break;
                default:
                    printf("Invalid operator: %c\n", ch);
                    return 1;
            }
        }
    }

    printf("Result: %.2f\n", pop(&stack));
    return 0;

    /*Remember data passed from command line is a char data type*/
    
    /* **Hint** You will need to perform stack operations that 
    we implemented here to achieve the expected output */
    
 
  
  

}