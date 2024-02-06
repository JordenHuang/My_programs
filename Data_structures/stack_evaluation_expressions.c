#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct stack{
    char data;
    struct stack *next;
}stack;


void stack_push(stack **top, char data){
    stack *new_node = (stack *)malloc(sizeof(stack));
    // strcpy(new_node->data, data);
    new_node->data = data;

    new_node->next = *top;
    *top = new_node;
}

char stack_pop(stack **top){
    stack *old_top = *top;
    char data = old_top->data;
    *top = (*top)->next;
    free(old_top);
    return data;
}


int precedence(char x){
    switch(x){
        case '+':case '-':
        return 0;

        case '*':case '/':case '%':
        return 1;

        case '^':
        return 2;

        default:
        return -1;
    }
}

int compare_precedence(char x, char y){
    int precedence_x = precedence(x);
    int precedence_y = precedence(y);
    
    if(precedence_x == precedence_y) return 0;
    else if(precedence_x > precedence_y) return 1;
    else return -1;
}

int is_operator(char a){
    char ops[] = "+-*/%^";
    int ops_len = strlen(ops);
    int i;
    for(i=0; i<ops_len; i++){
        if(a == ops[i]) return 1;
    }
    return 0;
}

int is_operand(char a){
    char opds[] = "1234567890";
    int opds_len = strlen(opds);
    int i;
    for(i=0; i<opds_len; i++){
        if(a == opds[i]) return 1;
    }
    return 0;
}


void infix_to_postfix(char *expressions, int len, char *result){
    stack *top = NULL;
    int i = 0, j;
    char cur, temp;

    int result_index = 0;

    while(i < len){
        cur = expressions[i];
        // printf("\ncur:%c\n", cur);
        
        // if it's an operand
        if(is_operator(cur) == 0 && cur != '(' && cur != ')'){
            // printf("%c", cur);
            result[result_index++] = cur;
        }
        // if it's a '('
        else if(cur == '('){
            stack_push(&top, cur);
        }
        // if it's a ')'
        else if(cur == ')'){
            temp = stack_pop(&top);
            while(temp != '('){
                // printf("%c", temp);
                result[result_index++] = temp;
                temp = stack_pop(&top);
            }
        }
        // if it's an operator
        else if(is_operator(cur)){
            if(top == NULL){
                stack_push(&top, cur);
            }
            else{
                temp = stack_pop(&top);
                j = compare_precedence(cur, temp);
                if(temp == '('){
                    stack_push(&top, temp);
                    stack_push(&top, cur);
                }
                else if(j != -1){
                    stack_push(&top, temp);
                    stack_push(&top, cur);
                }
                else{
                    while(j == -1){
                        // printf("%c", temp);
                        result[result_index++] = temp;

                        temp = stack_pop(&top);
                        j = compare_precedence(cur, temp);
                    }
                    stack_push(&top, temp);
                    stack_push(&top, cur);
                }
            }
        }
        i++;
    }

    // clear the stack
    while(top != NULL){
        temp = stack_pop(&top);
        // printf("%c", temp);
        result[result_index++] = temp;
    }
    result[result_index] = '\0';
}



int main(void){
    char expressions[] = "(((1+2)*(4*(4+6)-4))-(10*6))/6";
    char result[sizeof(expressions)/sizeof(char)];
    
    infix_to_postfix(expressions, strlen(expressions), result);

    printf("%s", result);
    return 0;
}

/*
如果要在讀入時把operator跟operand分開，而operand有兩位數時
我的想法是: 一位一位讀，如果是operator就直接讀好，如果是operand就先存入一個array
            然後讀下一位，如果還是operand就一樣存入，不是的話，就把整個array的轉為
            一個數 ( itoa() function )，這樣就不會要讀10，結果只讀到1跟0兩個分開的
*/


/*
TODO: infix to prefix, postfix to infix, prefix to infix,
 postfix to prefix, prefix to postfix, calculate postfix's result
*/