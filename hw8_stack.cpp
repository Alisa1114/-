#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

struct stackNode{

	char data;
	struct stackNode *nextPtr;
};

typedef struct stackNode StackNode;
typedef StackNode *StackNodePtr;

void convertToPostfix(char infix[], char postfix[]);
int isOperator(char c);
int precedence(char operator1, char operator2);
void push(StackNodePtr *topPtr, char value);
char pop(StackNodePtr *topPtr);
char stackTop(StackNodePtr topPtr);
int isEmpty(StackNodePtr topPtr);
void printStack(StackNodePtr topPtr);



int main(void){

	printf("½Ð¿é¤Jºâ¦¡¡G");

	char string1[MAX], string2[MAX] = { NULL };

	scanf("%s", string1);
	getchar();

	convertToPostfix(string1, string2);

	return 0;
}

void convertToPostfix(char infix[], char postfix[]){

	StackNodePtr stackPtr = NULL;

	size_t length = strlen(infix);
	int i, j;

	infix[length + 1] = ')';
	push(&stackPtr, '(');
	printStack(stackPtr);

	for (i = 0, j = 0; i <= length + 1; i++){

		switch (isOperator(infix[i])){

			case 1://operand
				postfix[++j] = infix[i];
				break;


			case 2://'('
				push(&stackPtr, infix[i]);
				printStack(stackPtr);
				break;

			case 3://operator
				if (!isEmpty(stackPtr)){
					switch (precedence(infix[i], stackTop(stackPtr))){

						case -1:case 0:
							postfix[++j] = pop(&stackPtr);
							push(&stackPtr, infix[i]);
							printStack(stackPtr);
							break;

						default:
							push(&stackPtr, infix[i]);
							printStack(stackPtr);
							break;
					}
				}
				else{

					push(&stackPtr, infix[i]);
					printStack(stackPtr);
				}
				break;

			default://')'
				while (!isEmpty(stackPtr) && stackTop(stackPtr) != '('){

					postfix[++j] = pop(&stackPtr);
					printStack(stackPtr);
				}
				if (stackTop(stackPtr) == '('){

					pop(&stackPtr);//pop '('
					printStack(stackPtr);
				}
				break;
		}
	}

	for (j = 0; postfix[j] != ')'; j++){

		if (postfix[j] != '(')
			printf("%c", postfix[j]);
	}

	system("pause");
}

int isOperator(char c){

	if (c == '('){

		return 2;
	}
	else if (c == ')'){

		return 4;
	}
	else if (c == '+' || c == '-' || c == '*' || c == '/' || c == '^' || c == '%'){

		return 3;
	}
	else{

		return 1;
	}
}

int precedence(char operator1, char operator2){

	if (operator2 == '('){

		return 1;
	}

	if (operator2 == '*' || operator2 == '/' || operator2 == '^' || operator2 == '%'){

		if (operator1 == '+' || operator1 == '-'){

			return -1;
		}
		else {

			return 0;
		}
	}
	else{

		if (operator1 == '+' || operator1 == '-'){

			return 0;
		}
		else{

			return 1;
		}
	}
}

void push(StackNodePtr *topPtr, char value){

	StackNodePtr newPtr = (StackNodePtr)malloc(sizeof(StackNode));

	if (newPtr != NULL){

		newPtr->data = value;
		newPtr->nextPtr = *topPtr;
		*topPtr = newPtr;
	}
	else{
		printf("%d not inserted. No memory available.\n", value);
	}
}

char pop(StackNodePtr *topPtr){

	StackNodePtr tempPtr = *topPtr;
	char popValue = (*topPtr)->data;
	*topPtr = (*topPtr)->nextPtr;
	free(tempPtr);
	return popValue;
}

int isEmpty(StackNodePtr topPtr){

	return topPtr == NULL;
}

void printStack(StackNodePtr topPtr){

	if (topPtr == NULL){
		puts("The stack is empty.\n");
	}
	else{
		puts("The stack is: ");

		while (topPtr != NULL){

			printf("%c --> ", topPtr->data);
			topPtr = topPtr->nextPtr;
		}

		puts("NULL\n");
	}
}

char stackTop(StackNodePtr topPtr){

	if (isEmpty(topPtr) == 0)
		return topPtr->data;
}