#include <stdio.h>
#include <stdlib.h>

struct Stack{
    int *array;
    int top;
    int capacity;
    char name;
};

struct Stack* createStack(int capacity, char name);

void push(struct Stack* Stack, int item);
int pop(struct Stack* Stack);
void movenums(int numitems, struct Stack* source, struct Stack* dest, struct Stack* aux);


int main() {
    int numitems;
    int i;

    // 輸入盤子總數
    printf("Enter the number of items:");
    scanf("%d", &numitems);

    // 建立三個柱子 A B C
    struct Stack* source = createStack(numitems, 'A');
    struct Stack* dest = createStack(numitems, 'C');
    struct Stack* aux = createStack(numitems, 'B');

    // 把盤子放進A柱,由大放到小
    for (i=numitems; i >= 1; i--){
        push(source, i);
    }

    // 開始河內塔遊戲
    movenums(numitems, source, dest, aux);

    return 0;
}

struct Stack* createStack(int capacity, char name) {
    /* stack裡面存了:
        capacity: 就是盤子的數量
        top: 紀錄top的位置
        array: 用陣列來當作stack來存放盤子的位置資料
        name: stack的名字(編號的概念)
    */
    struct Stack* stack = (struct Stack*)malloc(sizeof(struct Stack));
    stack->capacity = capacity;
    stack->top = -1;
    stack->array = (int*)malloc(capacity * sizeof(int));
    stack->name = name;
    return stack;
}
void push(struct Stack* Stack, int item) {
    // 紀錄並移動top的位置
    if (Stack->top < Stack->capacity - 1) {
        Stack->array[++Stack->top] = item;
    }
}
int pop(struct Stack* Stack) {
    // 紀錄並移動top的位置, 跟回傳該位置存的item (就是disk的編號)
    if (Stack->top >= 0) {
        return Stack->array[Stack->top--];
    }
    return -1;
}


void movenums(int numitems, struct Stack* source, struct Stack* dest, struct Stack* aux){
    // 遞迴的河內塔解法
    // recursion 的 movenums function
    // 如果盤子數量是1, recursion 的 base case
    // p.s aux是中繼站
    if (numitems == 1) {
        int item = pop(source);
        push(dest, item);
        printf("Move disk 1 from stack %c to stack %c\n", source->name, dest->name);
        return;
    }

    // 把上面的盤子移走
    movenums(numitems - 1, source, aux, dest);  // keep swaping the dest and aux, good
    
    // 移動自己
    int item = pop(source);
    push(dest, item);
    printf("Move disk %d from stack %c to stack %c\n", item /*numitems也可以*/, source->name, dest->name);
    
    // 把上面的盤子移回來
    movenums(numitems - 1, aux, dest, source);
}